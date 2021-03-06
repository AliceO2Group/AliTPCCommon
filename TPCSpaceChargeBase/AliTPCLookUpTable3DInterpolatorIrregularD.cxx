/**************************************************************************
 * Copyright(c) 1998-1999, ALICE Experiment at CERN, All rights reserved. *
 *                                                                        *
 * Author: The ALICE Off-line Project.                                    *
 * Contributors are mentioned in the code where appropriate.              *
 *                                                                        *
 * Permission to use, copy, modify and distribute this software and its   *
 * documentation strictly for non-commercial purposes is hereby granted   *
 * without fee, provided that the above copyright notice appears in all   *
 * copies and that both the copyright notice and this permission notice   *
 * appear in the supporting documentation. The authors make no claims     *
 * about the suitability of this software for any purpose. It is          *
 * provided "as is" without express or implied warranty.                  *
 **************************************************************************/

/// \class AliTPCLookUpTable3DInterpolatorIrregularD
/// \brief Wrap up look-up table with irregular grid
///
/// \author Rifki Sadikin <rifki.sadikin@cern.ch>, Indonesian Institute of Sciences
/// \date Mar 4, 2015


#include "AliTPCLookUpTable3DInterpolatorIrregularD.h"

/// \cond CLASSIMP3
ClassImp(AliTPCLookUpTable3DInterpolatorIrregularD)
/// \endcond


/// constructor
AliTPCLookUpTable3DInterpolatorIrregularD::AliTPCLookUpTable3DInterpolatorIrregularD() {
  fOrder = 1;
  fIsAllocatingLookUp = kFALSE;
}

/// constructor
///
/// \param nRRow
/// \param matricesRValue
/// \param matricesRPoint
/// \param nPhiSlice
/// \param matricesPhiValue
/// \param matricesPhiPoint
/// \param nZColumn
/// \param matricesZValue
/// \param matricesZPoint
/// \param order
/// \param stepR
/// \param stepZ
/// \param stepPhi
/// \param type
AliTPCLookUpTable3DInterpolatorIrregularD::AliTPCLookUpTable3DInterpolatorIrregularD(
        Int_t nRRow, TMatrixD **matricesRValue, TMatrixD **matricesRPoint, Int_t nPhiSlice, TMatrixD **matricesPhiValue,
        TMatrixD **matricesPhiPoint, Int_t nZColumn,
        TMatrixD **matricesZValue, TMatrixD **matricesZPoint, Int_t order, Int_t stepR, Int_t stepZ, Int_t stepPhi,
        Int_t type) {
  fIsAllocatingLookUp = kFALSE;

  SetNR(nRRow);
  SetLookUpR(matricesRValue);
  SetRList(matricesRPoint);
  SetNPhi(nPhiSlice);
  SetLookUpPhi(matricesPhiValue);
  SetPhiList(matricesPhiPoint);
  SetNZ(nZColumn);
  SetLookUpZ(matricesZValue);
  SetZList(matricesZPoint);
  SetOrder(order);

  fInterpolatorR = new AliTPC3DCylindricalInterpolatorIrregular(
          nRRow, nZColumn, nPhiSlice, stepR, stepZ, stepPhi, type);
  fInterpolatorZ = new AliTPC3DCylindricalInterpolatorIrregular(
          nRRow, nZColumn, nPhiSlice, stepR, stepZ, stepPhi, type);
  fInterpolatorPhi = new AliTPC3DCylindricalInterpolatorIrregular(
          nRRow, nZColumn, nPhiSlice, stepR, stepZ, stepPhi, type);

  fInterpolatorR->SetNR(nRRow);
  fInterpolatorR->SetNZ(nZColumn);
  fInterpolatorR->SetNPhi(nPhiSlice);

  fInterpolatorR->SetOrder(order);
  fInterpolatorZ->SetNR(nRRow);
  fInterpolatorZ->SetNZ(nZColumn);
  fInterpolatorZ->SetNPhi(nPhiSlice);
  fInterpolatorZ->SetOrder(order);
  fInterpolatorPhi->SetNR(nRRow);
  fInterpolatorPhi->SetNZ(nZColumn);
  fInterpolatorPhi->SetNPhi(nPhiSlice);
  fInterpolatorPhi->SetOrder(order);

}

/// destructor
AliTPCLookUpTable3DInterpolatorIrregularD::~AliTPCLookUpTable3DInterpolatorIrregularD() {

  if (fIsAllocatingLookUp) {
    for (Int_t m = 0; m < fNPhi; m++) {
      delete fMatricesRValue[m];
      delete fMatricesPhiValue[m];
      delete fMatricesZValue[m];
      delete fMatricesRPoint[m];
      delete fMatricesPhiPoint[m];
      delete fMatricesZPoint[m];
    }
    delete fMatricesRValue;
    delete fMatricesPhiValue;
    delete fMatricesZValue;
    delete fMatricesRPoint;
    delete fMatricesPhiPoint;
    delete fMatricesZPoint;
  }
  delete fInterpolatorR;
  delete fInterpolatorZ;
  delete fInterpolatorPhi;
}

/// copy from matrices to the interpolator
void AliTPCLookUpTable3DInterpolatorIrregularD::CopyFromMatricesToInterpolator() {

  fInterpolatorR->SetValue(fMatricesRValue, fMatricesRPoint, fMatricesPhiPoint, fMatricesZPoint);
  fInterpolatorZ->SetValue(fMatricesZValue, fMatricesRPoint, fMatricesPhiPoint, fMatricesZPoint);
  fInterpolatorPhi->SetValue(fMatricesPhiValue, fMatricesRPoint, fMatricesPhiPoint, fMatricesZPoint);
}

///
/// \param j
void AliTPCLookUpTable3DInterpolatorIrregularD::CopyFromMatricesToInterpolator(Int_t j) {
  fInterpolatorR->SetValue(fMatricesRValue, fMatricesRPoint, fMatricesPhiPoint, fMatricesZPoint, j);
  fInterpolatorZ->SetValue(fMatricesZValue, fMatricesRPoint, fMatricesPhiPoint, fMatricesZPoint, j);
  fInterpolatorPhi->SetValue(fMatricesPhiValue, fMatricesRPoint, fMatricesPhiPoint, fMatricesZPoint, j);
}

/// Get interpolation
/// \param r
/// \param phi
/// \param z
/// \param rValue
/// \param phiValue
/// \param zValue
/// \param rIndex
/// \param phiIndex
/// \param zIndex
/// \param stepR
/// \param stepPhi
/// \param stepZ
void AliTPCLookUpTable3DInterpolatorIrregularD::GetValue(
        Double_t r, Double_t phi, Double_t z, Double_t &rValue, Double_t &phiValue, Double_t &zValue,
        Int_t rIndex, Int_t phiIndex, Int_t zIndex, Int_t stepR, Int_t stepPhi, Int_t stepZ) {
  rValue = fInterpolatorR->GetValue(r, phi, z, rIndex, phiIndex, zIndex, stepR, stepPhi, stepZ);
  phiValue = fInterpolatorPhi->GetValue(r, phi, z, rIndex, phiIndex, zIndex, stepR, stepPhi, stepZ);
  zValue = fInterpolatorZ->GetValue(r, phi, z, rIndex, phiIndex, zIndex, stepR, stepPhi, stepZ);
}

/// Interpolation for a point (r,phi,z)
///
/// \param r
/// \param phi
/// \param z
/// \param rValue
/// \param phiValue
/// \param zValue
/// \param rIndex
/// \param phiIndex
/// \param zIndex
/// \param stepR
/// \param stepPhi
/// \param stepZ
/// \param minZColumnIndex
void AliTPCLookUpTable3DInterpolatorIrregularD::GetValue(
        Double_t r, Double_t phi, Double_t z, Double_t &rValue, Double_t &phiValue, Double_t &zValue, Int_t rIndex,
        Int_t phiIndex, Int_t zIndex, Int_t stepR, Int_t stepPhi, Int_t stepZ, Int_t minZColumnIndex
) {
  rValue = fInterpolatorR->GetValue(r, phi, z, rIndex, phiIndex, zIndex, stepR, stepPhi, stepZ, minZColumnIndex);
  phiValue = fInterpolatorPhi->GetValue(r, phi, z, rIndex, phiIndex, zIndex, stepR, stepPhi, stepZ, minZColumnIndex);
  zValue = fInterpolatorZ->GetValue(r, phi, z, rIndex, phiIndex, zIndex, stepR, stepPhi, stepZ, minZColumnIndex);
}


/// Get interpolation
/// \param r
/// \param phi
/// \param z
/// \param rValue
/// \param phiValue
/// \param zValue
/// \param rIndex
/// \param phiIndex
/// \param zIndex
/// \param startR
/// \param startPhi
/// \param startZ
void AliTPCLookUpTable3DInterpolatorIrregularD::GetValue(
        Double_t r, Double_t phi, Double_t z, Float_t &rValue, Float_t &phiValue, Float_t &zValue, Int_t rIndex,
        Int_t phiIndex, Int_t zIndex, Int_t startR, Int_t startPhi, Int_t startZ) {
  rValue = fInterpolatorR->GetValue(r, phi, z, rIndex, phiIndex, zIndex, startR, startPhi, startZ);
  phiValue = fInterpolatorPhi->GetValue(r, phi, z, rIndex, phiIndex, zIndex, startR, startPhi, startZ);
  zValue = fInterpolatorZ->GetValue(r, phi, z, rIndex, phiIndex, zIndex, startR, startPhi, startZ);
}

// using kdtree
void AliTPCLookUpTable3DInterpolatorIrregularD::GetValue(
        Double_t r, Double_t phi, Double_t z, Double_t &rValue, Double_t &phiValue, Double_t &zValue) {
  rValue = fInterpolatorR->GetValue(r, phi, z);
  phiValue = fInterpolatorPhi->GetValue(r, phi, z);
  zValue = fInterpolatorZ->GetValue(r, phi, z);
}

