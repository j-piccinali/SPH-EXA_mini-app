#include "contribution_interface.h"
#include "density_contribution.h"

#include <memory>

int main(int argc, char** argv)
{

  // A dummy parameter required by DensityContribution
  std::unique_ptr<int> fivePtr = std::move(std::make_unique<int>(5));

  // Contributions
  std::unique_ptr<IContribution> steps;
  {
    // Attach the first contribution "Core"
    steps = std::move(std::make_unique<CoreContribution>());


    // Attach "DensityContribution" to the existing steps (Core)
    //                      DensityContribution's constructor first argument  &    second argument
    //                                                                   v                   v
    steps = std::move(std::make_unique<DensityContribution>( std::move(steps), std::move(fivePtr)) );
  }
  // Now steps are ready!

  // Use steps the way you want
  // --------------------------
  std::size_t const nParticles = 100;

  // preprocess
  steps->preprocess();

  for (std::size_t iParticle=0; i<nParticles; ++i)
    // computation related to particle iParticle
    steps->compute(iParticle);

  // postprocess
  steps->finalize();

};
