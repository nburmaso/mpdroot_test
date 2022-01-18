/*
 * MpdV0Namespace.h
 *
 *  Created on: 16 gru 2021
 *      Author: Daniel Wielanek
 *      E-mail: daniel.wielanek at pw.edu.pl
 *      Warsaw University of Technology, Faculty of Physics
 *      JINR,  Laboratory of High Energy Physics
 */

#ifndef MPDROOT_PHYSICS_COMMON_V0_MPDV0NAMESPACE_H_
#define MPDROOT_PHYSICS_COMMON_V0_MPDV0NAMESPACE_H_

#include <RtypesCore.h>

namespace MpdCommonV0 {
enum class EParticleType { k0Short, kLambda, kAntiLambda };
enum class ESigmaType { kPionSigma, kKaonSigma, kProtonSigma };
Double_t GetMass(EParticleType type);
} // namespace MpdCommonV0

#endif /* MPDROOT_PHYSICS_COMMON_V0_MPDV0NAMESPACE_H_ */
