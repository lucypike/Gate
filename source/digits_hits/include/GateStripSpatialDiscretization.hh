

#ifndef GateStripSpatialDiscretization_h
#define GateStripSpatialDiscretization_h 1

#include "globals.hh"
#include <iostream>
#include <vector>
#include "G4ThreeVector.hh"
//#include "G4Types.hh"
#include "GateMaps.hh"
#include <set>

#include "GateVPulseProcessor.hh"

class GateStripSpatialDiscretizationMessenger;


class GateStripSpatialDiscretization : public GateVPulseProcessor
{
  public:

    //! Constructs a new pulse-adder attached to a GateDigitizer
    GateStripSpatialDiscretization(GatePulseProcessorChain* itsChain,const G4String& itsName);

    //! Destructor
    virtual ~GateStripSpatialDiscretization();

    //! Adds volume to the hashmap and returns 1 if it exists. If it does not exist, returns 0.
   G4int ChooseVolume(G4String val);


    //! Implementation of the pure virtual method declared by the base class GateClockDependent
    //! print-out the attributes specific of the pulse adder
    virtual void DescribeMyself(size_t indent);

    //! Set the threshold
    void SetThreshold(G4String name, G4double val) {  m_table[name].threshold = val;  };
    void SetStripOffsetX(G4String name, G4double val)   {  m_table[name].stripOffsetX = val;  };
    void SetStripOffsetY(G4String name, G4double val)   {  m_table[name].stripOffsetY = val;  };
    void SetNumberStripsX(G4String name,int val)   {  m_table[name].numberStripsX = val;  };
    void SetNumberStripsY(G4String name, int val)   {  m_table[name].numberStripsY = val;  };


     void SetVolumeName(G4String name) {
         G4cout<<"seting m_name Volume "<<name<<G4endl;
         m_name=name;};



protected:

  //! Implementation of the pure virtual method declared by the base class GateVPulseProcessor
  //! This methods processes one input-pulse
  //! It is is called by ProcessPulseList() for each of the input pulses
  //! The result of the pulse-processing is incorporated into the output pulse-list
  //void ProcessOnePulse(const GatePulse* inputPulse,GatePulseList& outputPulseList, std::vector<int> & indexX, std::vector<int>&  indexY);
  void ProcessOnePulse(const GatePulse* inputPulse,GatePulseList& outputPulseList);

//private:
  public:
  void ApplyEnergyThreshold( GatePulseList& outputPulseList);
   void ApplyNeighbouringConditions( GatePulseList& outputPulseList);
 GatePulseList* ProcessPulseList(const GatePulseList* inputPulseList);

  std::vector<int > index_X_list;
  std::vector<int > index_Y_list;

  struct param {

      G4double threshold;
      G4double stripOffsetX;
      G4double stripOffsetY;
      G4int numberStripsX;
      G4int numberStripsY;
  };
     param m_param;

    G4String m_name;                               //! Name of the volume
    GateStripSpatialDiscretizationMessenger *m_messenger;     //!< Messenger
    GateMap<G4String,param> m_table ;  //! Table which contains the names of volume with their characteristics
    GateMap<G4String,param> ::iterator im;  //! iterator of the gatemap
    double* sizeVol;
    double pitchX;
    double pitchY;

    //void GetGridPoints2D(G4ThreeVector& pos );
    void SetGridPoints2D( int indexX, int indexY, G4ThreeVector& pos );

    double GetXIndex(G4double posX);
    double GetYIndex(G4double posY);

	//several functions needed for special processing of electronic pulses
	void PulsePushBack(const GatePulse* inputPulse, GatePulseList& outputPulseList);



};


#endif
