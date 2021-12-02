
        _RB15 = 1;
        __delay_ms(10);
        _RB15 = 0;
        __delay_ms(10);

        //***** Motor control *****
        update_direction1(0);
        pulse_ntimes1(50); //16 full revs
        __delay_ms(5);
        update_direction2(0);
        pulse_ntimes2(50);
        //update_direction2(1);
        //pulse_ntimes2(50);
        //update_direction1(0);
        //pulse_ntimes1(50);
        //update_direction2(0);
        //pulse_ntimes2(50);

        __delay_ms(5);
        //update_direction2(1);
        pulse_simultaneous_ntimes(50);
        //*************************************


        //***** LCD Control in main *****
         //clear_LCD();
        delay_cycles(5);
        reset_cursor(); //put cursor back to 0,0
        delay_cycles(5);
        ultoa(buffer, counter, 10);//convert int to unsigned char.
        //have to set -no-legacy-libc in XC16 global properties to get this function

        if(_RA0 == 0)
        {
        Show("RA0 Pressed             ");
        }

        else
        {
         Show("Please Press Button            ");
        }
        //move_cursor(0, 7); //move cursor to 0,7.
        //Show(buffer); //display current count
        //delay_cycles(500);
        //move_cursor(1, 0); //move cursor to 1,0 (second line, position 0)
        //Show("Team 5, Checkoff 2            ");
        move_cursor(1, 8);
        Show(buffer);
        //Show(buffer); //display current count
        delay_cycles(5);
        counter = counter +1;
        __delay_ms(5);
