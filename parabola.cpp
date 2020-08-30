#include <iostream>
#include <utility>
#include <cmath>
using namespace std;

typedef pair<pair<double,double>,double> coord ;

#define X first.first
#define Y first.second
#define Z second

void affect(coord &a,const coord b,double DELTA){
	a.X+=b.X*DELTA;
	a.Y+=b.Y*DELTA;
	a.Z+=b.Z*DELTA;
}

const double DELTA=1e-5;

int main(){
	coord pos;
	cin>>pos.X>>pos.Y;
	pos.Z=0;
	coord vel;
	int power;
	float heading;
	float angle;
	cin>>power>>heading>>angle;
	vel.X=vel.Z=0;
	vel.Y=power;
	//rotate around X
	////cerr<<angle*M_PI/180<<' '<<sin(angle*M_PI/180)<<' '<<cos(angle*M_PI/180)<<'\n';
	vel.Z=vel.Y*sin(angle*M_PI/180);
	vel.Y=vel.Y*cos(angle*M_PI/180);
	//rotate around Z
	vel.X=-sin(heading*M_PI/180)*vel.Y;
	vel.Y*=cos(heading*M_PI/180);
	//forces
	
	coord grav;
	grav.X=grav.Y=0;
	grav.Z=-10;//magic number, but the only place where it is used

	coord wind;
	float windHeading;
#define WS 3
	cin>>windHeading;
	wind.Z=0;
	wind.X=-sin(windHeading*M_PI/180)*WS;
	wind.Y=cos(windHeading*M_PI/180)*WS;

	////cerr<<"vel=("<<vel.X<<','<<vel.Y<<','<<vel.Z<<')'<<'\n';
	do{
		affect(pos,vel,DELTA);
		////cerr<<"vel=("<<vel.X<<','<<vel.Y<<','<<vel.Z<<')'<<'\n';
		affect(vel,wind,DELTA);
		////cerr<<"vel=("<<vel.X<<','<<vel.Y<<','<<vel.Z<<')'<<'\n';
		affect(vel,grav,DELTA);
		////cerr<<"vel=("<<vel.X<<','<<vel.Y<<','<<vel.Z<<')'<<'\n';
//		cerr<<pos.X<<' '<<pos.Y<<' '<<pos.Z<<'\n';
	}while(pos.Z>0);
	cout<<round(pos.X)<<' '<<round(pos.Y)<</*' '<<pos.Z<<*/'\n';
}
