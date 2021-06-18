#ifndef TRACKBALL_H
#define TRACKBALL_H

#include <string>
#include <fstream>

class TrackBall
{
    std::string TrackBallName;

public:
    enum constructType {undef = 0, midlle_ball, side_ball};
    enum  manufacturer{Undef = 0, Cubase, Pro_Tools, Logic, Studio_One};

private:
    constructType conType;
    manufacturer mfact;
    int sensitivity;
    int buttonsAm;
    mutable bool wireless;
public:
    TrackBall();
    TrackBall(std::string trackballName);

    TrackBall (const std::string ltrackballName,
               const constructType lconType,
               const manufacturer lmfact,
               const int lsensitivity,
               const int lbuttonsAm,
               const bool lwireless);
    ~TrackBall();

    TrackBall(const TrackBall &other);

    void  setConstructType(const constructType lconType);
    constructType  getConstructType() const {return conType;}

    void  setmfact(const manufacturer lmfact);
    manufacturer  getmfact() const {return mfact;}

    void setTrackballName(const std::string lTbName);
    std::string getTrackballName() const;

    void setWireless(const bool lwireless);
    bool getWireless() const {return wireless;}

    void setSensitivity(const int lsensitivity);
    int getSensitivity() const {return sensitivity;}

    void setButtons(const int lbuttons);
    int getButtons() const {return buttonsAm;}


    void display() const;

};

#endif // TRACKBALL_H
