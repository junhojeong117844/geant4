#ifndef FIELD
#define FIELD

#include "G4ElectroMagneticField.hh"

class Field : public G4ElectroMagneticField
{
  public:
    Field() {}
    virtual ~Field() {}

    virtual G4bool DoesFieldChangeEnergy() const { return false; }

    virtual void GetFieldValue(const G4double point[4], G4double *field) const;
};

#endif
