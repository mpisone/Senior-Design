// MPU6050
// Senior Design Team 5

// Main Program Calculates Position

#include "MPU6050.h"
#include <stdlib.h>

// declare imu object 
MPU6050 imu(0x68);

#define x_offset  0.58;
#define y_offset  1.10;
#define z_offset  0.95;


// uncomment to obrain offset information
/*
void getOffsets(float *ax_off, float *ay_off, float *az_off, float *gr_off, float *gp_off, float *gy_off) {

	std::cout << "Calibrating IMU Sensor \nThis may take several minutes\n";


	float gyro_off[3]; //Temporary storage
	float accel_off[3];

	*gr_off = 0, *gp_off = 0, *gy_off = 0; //Initialize the offsets to zero
	*ax_off = 0, *ay_off = 0, *az_off = 0; //Initialize the offsets to zero

	for (int i = 0; i < 10000; i++) { //Use loop to average offsets
		imu.getGyroRaw(&gyro_off[0], &gyro_off[1], &gyro_off[2]); //Raw gyroscope values
		*gr_off = *gr_off + gyro_off[0], *gp_off = *gp_off + gyro_off[1], *gy_off = *gy_off + gyro_off[2]; //Add to sum

		imu.getAccRaw(&accel_off[0], &accel_off[1], &accel_off[2]); //Raw accelerometer values
		*ax_off = *ax_off + accel_off[0], *ay_off = *ay_off + accel_off[1], *az_off = *az_off + accel_off[2]; //Add to sum
	}

	// *gr_off = *gr_off / 10000, *gp_off = *gp_off / 10000, *gy_off = *gy_off / 10000; //Divide by number of loops (to average)
	*ax_off = *ax_off / 10000, *ay_off = *ay_off / 10000, *az_off = *az_off / 10000;
	
	*az_off = *az_off - ACCEL_SENS; //Remove 1g from the value calculated to compensate for gravity)

	std::cout << "offsets are: X: " << ax_off << ", Y: " << ay_off << ", Z: " << az_off << "\n";

}
*/
// float getVelocity(float *da0, float *da1, int *dt){
	// float v;
	// v = (da1 - da0) * dt;
// }

	float getDist(float da0, float da1, int dt){
		float dist = 0.0;
		float avga;
		avga = (da1 + da0)/2.0;
		float t = static_cast<float>(dt);
		dist = 0.5 * avga*avga / t;
		return dist;
	}


int main() {
	// initialize variables 
	float ax, ay, az;
	// float gr, gp, gy; 
	float ax0, ay0;
	float ax1, ay1;
	float dx0, dy0;
	float distx, disty, dist;
	// float az0, az1, dz0;


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

	// imu.getOffsets(&ax, &ay, &az, &gr, &gp, &gy);

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

// penetrate drifting noise
		do {
			// get dx0, dy0, dz0
			imu.getAcc(&ax, &ay, &az);
			ax0 = ax;
			ay0 = ay;
			// az0 = az;

			usleep(1000); 
			imu.getAcc(&ax, &ay, &az);
			ax1 = ax;
			ay1 = ay;
			// az1 = az;

			dx0 = ax1 - ax0;
			dy0 = ay1 - ay0;
			// dz0 = az1 - az0;
			if (dx0 < 0.1)
				ax = 0;
			if (dy0 < 0.1)
				ay = 0;
			std::cout << "Accelerometer Readings: X: " << ax << ", Y: " << ay << "\n";


			// if (dz0 < 0.01)
			// 	az = az0;
			// std::cout << "Accelerometer Readings: X: " << ax << ", Y: " << ay << ", Z: " << az << "\n";

		} while (abs(ax)==0 && abs(ay)==0);


		imu.getAcc(&ax, &ay, &az);
		ax = ax + x_offset;
		ay = ay + y_offset;
		az = az + z_offset;
		distx = getDist(ax0, ax1, 0.001);
		disty = getDist(ay0, ay1, 0.001);
		dist = sqrt(distx*distx + disty*disty);
		// std::cout << "Accelerometer Readings: X: " << ax << ", Y: " << ay << ", Z: " << az << "\n";
		std::cout << "Displacement along axes are: X: " << distx << ", Y: " << disty << "\n";
		std::cout << "Displacement Combination is: " << dist;

		usleep(1000000); // read data per 1 second ( 10^6 micro-seconds )
	}

	// function to get acc
	// imu.getAcc(&ax, &ay, &az);

	// std::cout << "Accelerometer : X: " << ax << ", Y: " << ay << ", Z: " << az << "\n";

	// function to get gyro
	// imu.getGyro(&gr, &gp, &gy);
	// std::cout << "Gyroscope : X: " << gr << ", Y: " << gp << ", Z: " << gy << "\n";

	return 0;
}


