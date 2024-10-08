// CNCHolePattern.cpp : This file contains the 'main' function. Program execution begins and ends there.
// MJH:10_07_2024:manual cnc drill pattern output tap file for use on omio cnc
// MJH:10_08_2024:update to create gcode tap files automatically from 1 to 50 
// test3

#include <iostream>
#include <fstream>
#include <string>



int main() {
    // set speed and feed
    int spindle{ 9000 };
    int feed{ 450 };
    int holes{ 50 }; // max number of holes

    // loop through from 1 to holes
    int Hcount{ 1 }; // loop Hcount from 1 to holes
    while (Hcount <= holes) {
        //create output filename
        std::string fname = ("3x" + std::to_string(Hcount) + "_Alum_HolePattern.tap");
        std::ofstream outf{ fname };
        // If we couldn't open the output file stream for writing
        if (!outf)
        {
            // Print an error and exit
            std::cerr << "Uh oh, Sample.txt could not be opened for writing!\n";
            return 1;
        }
        // print out manually the startup gcode 
        outf << "(ALUM 1X HOLE PATTERN)\n";
        outf << "(T7  D=4.978 CR=0. TAPER=135DEG - ZMIN=-5.206 - DRILL)\n";
        outf << "G90 G94 G91.1 G40 G49 G17\n";
        outf << "G21\n";
        outf << "(OPERATION COMMENT 9DRILL ALUM HOLE PATTERN)\n";
        outf << "M5\n";
        outf << "T7 M6\n";
        outf << "S" << spindle << " M3\n";
        outf << "G54\n";
        outf << "(4419 POST EDIT TO FORCE Z AXIS MOVE BEFORE G0)\n";
        outf << "(UNIT = 1 0 = INCH 1 = MM)\n";
        outf << "G1 Z10 F500.\n";
        outf << "(4419 END OF EDIT)\n";
        outf << "G0 X0. Y0.\n";
        outf << "G43 Z16.24 H7\n";
        outf << "Z6.0\n";
        outf << "G98 G81 X0. Y0. Z-5.0 R5.08 F" << feed << ".\n";
        outf << "X12.7" << "\n";
        outf << "X25.4" << "\n";

        //loop while for each x hole move 12.7mm in Y
        double yDist = { 12.7 };
        int Ycount{ 1 };
        // count -1 bc hole 1 is at Y0.0
        while (Ycount <= (Hcount - 1)) {
            outf << "X0." << " Y" << (yDist * Ycount) << "\n";
            outf << "X12.7" << " Y" << (yDist * Ycount) << "\n";
            outf << "X25.4" << " Y" << (yDist * Ycount) << "\n";
            ++Ycount;
        }
        // closing print gcode
        outf << "G80\n";
        outf << "Z15\n";
        outf << "M30\n";
        ++Hcount;
    }
}