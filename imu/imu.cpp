// MPU6050
// Senior Design Team 5

// Main Program Calculates Position

#include "MPU6050.h"
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <unistd.h>

// declare imu object 
MPU6050 imu(0x68);


// uncomment to obrain offset information

void getOffsets(float *ax_off, float *ay_off, float *az_off, float *stddevx, float *stddevy, float *stddevz) {

	std::cout << "Calibrating IMU Sensor \nThis may take several minutes\n";

	int n = 1000; // loop cycles for mean
	// float gyro_off[3]; //Temporary storage
	float acc[] = {0, 0, 0};
	float meanx, meany, meanz;
	float arrx[n];
	float arry[n];
	float arrz[n];


	// *gr_off = 0, *gp_off = 0, *gy_off = 0; //Initialize the offsets to zero
	*ax_off = 0, *ay_off = 0, *az_off = 0; //Initialize the offsets to zero
	*stddevx = 0; *stddevy = 0; *stddevz = 0;

	for (int i = 0; i < n; i++) { //Use loop to average offsets
		// imu.getGyro(&gyro_off[0], &gyro_off[1], &gyro_off[2]); //Raw gyroscope values
		// *gr_off = *gr_off + gyro_off[0], *gp_off = *gp_off + gyro_off[1], *gy_off = *gy_off + gyro_off[2]; //Add to sum

		imu.getAcc(&acc[0], &acc[1], &acc[2]); //Raw accelerometer values
		// std::cout << "readings are: X: " << acc[0] << ", Y: " << acc[1] << ", Z: " << acc[2] << "\n";
		*ax_off = *ax_off + acc[0]; 
		*ay_off = *ay_off + acc[1];
		*az_off = *az_off + acc[2];
		arrx[i] = acc[0];
		arry[i] = acc[1];
		arrz[i] = acc[2];
		usleep(1000);
	}
	meanx = *ax_off / n;
	meany = *ay_off / n;
	meanz = *az_off / n;

	for (int i = 0; i < n; i++){
		*stddevx += (arrx[i] - meanx) * (arrx[i] - meanx);
		*stddevy += (arry[i] - meany) * (arry[i] - meany);
		*stddevz += (arrz[i] - meanz) * (arrz[i] - meanz);
	}

	*stddevx /= n;
	*stddevy /= n;
	*stddevz /= n;
	*stddevx = sqrt(abs(*stddevx));
	*stddevy = sqrt(abs(*stddevy));
	*stddevz = sqrt(abs(*stddevz));

	std::cout << "offsets by mean are: X: " << meanx << ", Y: " << meany << ", Z: " << meanz << "\n";
	std::cout << "stddevs are X: " << *stddevx << ", Y: " << *stddevy << ", Z: " << *stddevz << "\n";

}
	


// calculate std dev of stable noise
// void getstddev (float* std_ax, float* std_ay, float* std_az, int samples){
	
// 	// popup info
// 	std::cout << "Calibrating IMU Sensor \nThis may take several minutes\n";

// 	// create file
// 	std::ofstream accRead;
// 	accRead.open("stableAcc.csv");

// 	float acc[3];

// 	for (int i = 0; i < samples; i++){
// 		imu.getAcc(&acc[0], &acc[1], &acc[2]);
// 		accRead << acc[0] << "," << acc[1] << "," << acc[2] << "\n";
// 		std::cout << "Accelerometer Readings: X: " << acc[0] << ", Y: " << acc[1] << "\n";
// 		sleep(1);
// 	}
// 	accRead.close();

// }





// float getVelocity(float *da0, float *da1, int *dt){
	// float v;
	// v = (da1 - da0) * dt;
// }

	float getDist(float a, float dt){
		float dist = 0.0;
		// float avga;
		// avga = (da1 + da0)/2.0;
		// float t = static_cast<float>(dt);
		// dist = 0.5 * avga*avga / t;

		dist = 0.5*a*dt*dt;
		return dist;
	}

	float distCombine(float distx, float disty, float distz){
		// return sqrt(distx*distx + disty*disty);
		return sqrt(distx*distx + disty * disty + distz * distz);
	}

	// float integral(float up, float lo, float x, float t){
	// 	float result = 0;
	// 	step = (up - lo)/
	// 	return result;
	// }


int main() {
	float x_offset;
	float y_offset;
	float z_offset;
	float stddevx;
	float stddevy;
	float stddevz;


	// initialize variables 
	float ax, ay, az;
	// float gr, gp, gy; 
	float ax0, ay0;
	float ax1, ay1;
	float dx0, dy0;
	float distx, disty, dist;
	float distz;
	float az0, az1, dz0;
	float ax_denoised = 0.0;
	float ay_denoised = 0.0;
	float az_denoised = 0.0;
	float cumDist;

	int counter;


 /*  description of variables
	x - longer edege
	y - shorter edge,
	z - vertical axis
	gr longer edge rotation
	gp shorter edge rotation
	gy horizontal roation (not stable, drift problem and keeps changing)
*/

	// time allowed to warm up sensor to get stablized read
	sleep(1); 

	// currently not used 
	// imu.calc_yaw = true;
	imu.calc_yaw = false;

	getOffsets(&x_offset, &y_offset, &z_offset, &stddevx, &stddevy, &stddevz);
	// getstddev(&ax, &ay, &az, 1000);

	sleep(3);


	std::ofstream accRead;
	accRead.open("accRead.csv");

	while(true) {
// ****** initialize temp variables -- currently not used
		// float dx, dy;
		// dx = 0.0;
		// dy = 0.0;

// ****** measure angle -- currently not used
		// imu.getAngle(0, &gr);
		// imu.getAngle(1, &gp);
		// imu.getAngle(2, &gy);
		// std::cout << "Current angle around the roll axis: " << gr << "\n";
		// std::cout << "Current angle around the pitch axis: " << gp << "\n";
		// std::cout << "Current angle around the yaw axis: " << gy << "\n";

// compensate drifting noise
	
		
		if (ax_denoised!=0 || ay_denoised!=0 || az_denoised != 0){

			distx = getDist(ax_denoised * 9.8 * 1000, 0.001);
			disty = getDist(ay_denoised * 9.8 * 1000, 0.001);
			distz = getDist(az_denoised * 9.8 * 1000, 0.001); 
			dist = distCombine(distx, disty, distz);
			cumDist += dist;
			// std::cout << "Accelerometer Readings: X: " << ax << ", Y: " << ay << ", Z: " << az << "\n";
			

			counter++;



			// if (counter == 10) {
			// 	counter = 0;
			accRead << ax_denoised << "," << ay_denoised << "," << az_denoised << "," << distx << "," << disty << "," << distz << "," << dist << "," << cumDist << "\n";
			std::cout << "Displacement along axes are: X: " << distx << ", Y: " << disty << "\n";
			std::cout << "Displacement Combination is: " << dist << "\n";
			std::cout << "Cumulative Displacement is: " << cumDist << "\n";
			// }

		}


		if (ax_denoised ==0 || ay_denoised ==0 || az_denoised == 0) {
			cumDist = 0;
		}


		// get dx0, dy0, dz0
		imu.getAcc(&ax, &ay, &az);
		ax0 = ax;
		ay0 = ay;
		az0 = az;

		usleep(10); 
		imu.getAcc(&ax, &ay, &az);
		ax1 = ax;
		ay1 = ay;
		az1 = az;

		dx0 = ax1 - ax0;
		dy0 = ay1 - ay0;
		dz0 = az1 - az0;

		// denoise and get real acceleration

		if (dx0 < stddevx)
			ax_denoised = 0;
		else
			ax_denoised = dx0 - stddevx;

		if (dy0 < stddevy)
			ay_denoised = 0;
		else
			ay_denoised = dy0 - stddevy;

		if (dz0 < stddevz)
			az_denoised = 0;
		else
			az_denoised = dz0 - stddevz;

		// std::cout << "Accelerometer Readings: X: " << ax_denoised << ", Y: " << ay_denoised << "\n";


		// if (dz0 < 0.01)
		// 	az = az0;
		// std::cout << "Accelerometer Readings: X: " << ax << ", Y: " << ay << ", Z: " << az << "\n";

		// getDist(ax_denoised, ay_denoised, 0.001)

		


		// usleep(1000); // read data per 1 second 
	}

	// function to get acc
	// imu.getAcc(&ax, &ay, &az);

	// std::cout << "Accelerometer : X: " << ax << ", Y: " << ay << ", Z: " << az << "\n";

	// function to get gyro
	// imu.getGyro(&gr, &gp, &gy);
	// std::cout << "Gyroscope : X: " << gr << ", Y: " << gp << ", Z: " << gy << "\n";

	accRead.close();

	return 0;
}
