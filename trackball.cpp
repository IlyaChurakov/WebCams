#include <iostream>
#include <iomanip>
#include "TrackBall.h"

using namespace std;

TrackBall::TrackBall():
    TrackBallName(""),
    conType(undef),
    mfact(Undef),
    sensitivity(0),
    wireless(0)
{

}

TrackBall::TrackBall(string recordNameTrackBall):
    TrackBallName(recordNameTrackBall)
{

}

TrackBall::TrackBall(const string lTrackBallName,
                     const TrackBall::constructType lconType,
                     const TrackBall::manufacturer lmfact,
                     const int lsensitivity,
                     const int lBtns,
                     const bool lwireless):
    TrackBallName(lTrackBallName)
  , conType(lconType)
  , mfact(lmfact)
  , sensitivity(lsensitivity)
  , buttonsAm(lBtns)
  , wireless(lwireless )
{

}

TrackBall::~TrackBall()
{

}

TrackBall::TrackBall(const TrackBall &other):
    TrackBallName(other.TrackBallName)
  , conType(other.conType)
  , mfact(other.mfact)
  , sensitivity(other.sensitivity)
  , wireless(other.wireless)
{

}

void TrackBall::setConstructType(const TrackBall::constructType lconType)
{
    conType = lconType;
}

void TrackBall::setmfact(const TrackBall::manufacturer lmfact)
{
    mfact = lmfact;
}

void TrackBall::setTrackballName(const std::string lTbName)
{
    TrackBallName = lTbName;
}

std::string TrackBall::getTrackballName() const
{
    return TrackBallName;
}

void TrackBall::setWireless(const bool lwireless)
{
    wireless = lwireless;
}

void TrackBall::setSensitivity(const int lsensitivity)
{
    sensitivity = lsensitivity;
}

void TrackBall::setButtons(const int lbuttons)
{
    buttonsAm = lbuttons;
}

void TrackBall::display() const
{
    const char* strConstType[] = {"undef", "midlle_ball", "side_ball"};
        const char* strManufacturer[] = {"Undef", "Cubase", "Pro_Tools", "Logic", "Studio_One"};

        cout << boolalpha
             << "   Trackball Name: " << getTrackballName()
             << "\n   Construct Type: " << strConstType[getConstructType()]
             << "\n   Manufacturer: " << strManufacturer[getmfact()]
             << "\n   Sensitivity: " << getSensitivity()
             << "\n   Wireless: " << getWireless()
             << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
}
