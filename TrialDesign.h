#ifndef PHARMML_TRIALDESIGN_H_
#define PHARMML_TRIALDESIGN_H_

#include <libxml/parser.h>
#include <libxml/tree.h>
#include "PharmMLContext.h"
#include "ExternalDataset.h"
#include "Interventions.h"
#include "Observations.h"
#include "Arms.h"
#include "DesignSpaces.h"

namespace PharmML
{
    class TrialDesign
    {
        PharmML::PharmMLContext *context;
        PharmML::Interventions *Interventions = nullptr;
        PharmML::ExternalDataset *ExternalDataset = nullptr;
        PharmML::Observations *Observations = nullptr;
        PharmML::Arms *Arms = nullptr;
        PharmML::DesignSpaces *DesignSpaces = nullptr;

        public:
        PharmML::ExternalDataset *getExternalDataset();
        PharmML::Interventions *getInterventions();
        PharmML::Observations *getObservations();
        PharmML::Arms *getArms();
        PharmML::DesignSpaces *getDesignSpaces();
        TrialDesign(PharmML::PharmMLContext *context, xml::Node node);
        void parse(xml::Node node);
    };
}

#endif
