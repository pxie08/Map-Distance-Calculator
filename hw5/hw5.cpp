/****************************************************
**hw5.cpp
**Map of Middle Earth
**Patrick Xie, (02/12/2010)
*****************************************************/

#include "ccc_win.h"
#include <string>
#include <cmath>
using namespace std;

double distance2points();
double distancePointLine();

//Global Constants
Point theShire (128,282);
Point mtDoom (333,158);
Point dolAmroth(209,124);
Point rivendell (198,301);
Point erebor (318,327);
Point moria (208,247);

/****************************************************
**drawMap: draws the outline including the locations
**Parameters: nothing
**returns: nothing
*****************************************************/
void drawMap(){
	cwin.coord( -50, 450, 550, -225);
	//Grid
	cwin<< Line (Point(0,0),Point(500,0))
		<< Line (Point(0,0),Point(0,400))
		<< Line (Point(500,0),Point(500,400))
		<< Line (Point(500,400),Point(0,400));
	//ticks on y-axis
	cwin<< Line (Point(-10,0),Point(10,0))
		<< Line (Point(-10,100),Point(10,100))
		<< Line (Point(-10,200),Point(10,200))
		<< Line (Point(-10,300),Point(10,300))
		<< Line (Point(-10,400),Point(10,400));
	//ticks on x-axis
	cwin<< Line (Point(0,-10),Point(0,10))
		<< Line (Point(100,-10),Point(100,10))
		<< Line (Point(200,-10),Point(200,10))
		<< Line (Point(300,-10),Point(300,10))
		<< Line (Point(400,-10),Point(400,10))
		<< Line (Point(500,-10),Point(500,10));
	//labels for y-axis
	cwin<< Message (Point(-35,106),100)
		<< Message (Point(-35,206),200)
		<< Message (Point(-35,306),300)
		<< Message (Point(-35,406),400);
	//labels for x-axis
	cwin<< Message (Point(90,-12),100)
		<< Message (Point(190,-12),200)
		<< Message (Point(290,-12),300)
		<< Message (Point(390,-12),400)
		<< Message (Point(490,-12),500);
	//Points on the map
	cwin<< Point(theShire)
		<< Point(mtDoom)
		<< Point(dolAmroth)
		<< Point(rivendell)
		<< Point(erebor)
		<< Point(moria);
	//Labeling Points on the map
	cwin<< Message (Point(theShire),"The Shire")
		<< Message (Point(mtDoom),"Mt. Doom")
		<< Message (Point(dolAmroth),"Dol Amroth")
		<< Message (Point(rivendell),"Rivendell")
		<< Message (Point(erebor),"Erebor")
		<< Message (Point(moria),"Moria");
}


/****************************************************
**distance2points:distance between two points
**Parameters:two points 
**returns:int distance between the two points
*****************************************************/
double distance2points(Point(mouseclick1),Point(mouseclick2)){
	double x1 = mouseclick1.get_x();
	double y1 = mouseclick1.get_y();
	double x2 = mouseclick2.get_x();
	double y2 = mouseclick2.get_y();
	double a1 = x1 - x2;
	double b1 = y1 - y2;
	double a2 = pow(a1,2);
	double b2 = pow(b1,2);
	double a2plusb2 = a2 + b2;
	double distance = sqrt(a2plusb2);
	return distance;
}


/****************************************************
**distancePointLine: counts distance from point to line
**Parameters:point from location, first click, and second click
**returns:distance from point to line
*****************************************************/
double distancePointLine(Point(location),Point(click1),Point(click2)){
	double a = location.get_x();
	double b = location.get_y();
	double x1 = click1.get_x();
	double y1 = click1.get_y();
	double x2 = click2.get_x();
	double y2 = click2.get_y();

	double t = ((a-x1)*(x2-x1)+(b-y1)*(y2-y1))/(pow((x2-x1),2)+pow((y2-y1),2));

	if (t <= 0){
		double distanceFromLine = sqrt((pow((a-x1),2)+pow((b-y1),2)));
		return distanceFromLine;
	}
	else if (t > 0 && t < 1){
		double distanceFromLine = sqrt((pow((a-x1-t*x2+t*x1),2)+pow((b-y1-t*y2+t*y1),2)));
		return distanceFromLine;
	}
	else if (t >= 1){
		double distanceFromLine = sqrt((pow((a-x2),2)+pow((b-y2),2)));
		return distanceFromLine;
	}
}


int ccc_win_main() {
	//declaring response variable for the loop of the program
	string response;
	do {
		//draws the map of middle earth
		drawMap();
		//gets mouse inputs for the starting and end point
		Point startPoint = cwin.get_mouse ("Click on your starting point.");
		cwin<< startPoint;
		Point endPoint = cwin.get_mouse ("Click on your ending point.");
		cwin<< endPoint;
		//shows how far the two points are from each other in a straight line
		cwin<< Line(Point(startPoint),Point(endPoint));
		cwin<< Message (Point (0,-50),"Total distance in miles: ");
		cwin<< Message (Point(150,-50),distance2points(startPoint,endPoint));
		//uses function to calculate the distance from the line to a point location
		double distance_theShire = distancePointLine(Point(theShire),Point(startPoint),Point(endPoint));
		double distance_mtDoom = distancePointLine(Point(mtDoom),Point(startPoint),Point(endPoint));
		double distance_dolAmroth = distancePointLine(Point(dolAmroth),Point(startPoint),Point(endPoint));
		double distance_rivendell = distancePointLine(Point(rivendell),Point(startPoint),Point(endPoint));
		double distance_erebor = distancePointLine(Point(erebor),Point(startPoint),Point(endPoint));
		double distance_moria = distancePointLine(Point(moria),Point(startPoint),Point(endPoint));
		//if statements to output message if the line is within 25 miles of a point location
		if (distance_theShire <= 25){
			cwin<< Message (Point(0,-75),"You pass within 25 miles of The Shire, and is this many miles away from it:");
			cwin<< Message (Point(475,-75),distance_theShire);
		}
		if (distance_mtDoom <= 25){
			cwin<< Message (Point(0,-100),"You pass within 25 miles of Mt. Doom, and is this many miles away from it:");
			cwin<< Message (Point(475,-100),distance_mtDoom);
		}
		if (distance_dolAmroth <= 25){
			cwin<< Message (Point(0,-125),"You pass within 25 miles of Dol Amroth, and is this many miles away from it:");
			cwin<< Message (Point(485,-125),distance_dolAmroth);
		}
		if (distance_rivendell <= 25){
			cwin<< Message (Point(0,-150),"You pass within 25 miles of Rivendell, and is this many miles away from it:");
			cwin<< Message (Point(475,-150),distance_rivendell);
		}
		if (distance_erebor <= 25){
			cwin<< Message (Point(0,-175),"You pass within 25 miles of Erebor, and is this many miles away from it:");
			cwin<< Message (Point(460,-175),distance_erebor);
		}
		if (distance_moria <= 25){
			cwin<< Message (Point(0,-200),"You pass within 25 miles of Moria, and is this many miles away from it:");
			cwin<< Message (Point(455,-200),distance_moria);
		}
		//gives user a choice of restarting the program or not
		response = cwin.get_string("Mark the map again? (y/n): ");
		cwin.clear();
	} while (response == "y" || response == "Y");
	cwin.clear();
	return 0;
}
