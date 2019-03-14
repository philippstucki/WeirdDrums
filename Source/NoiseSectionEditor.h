/*
  ==============================================================================

    NoiseSectionEditor.h
    Created: 6 Nov 2018 4:44:43pm
    Author:  dfila

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "LookAndFeels.h"
#include "LtdRotarySlider.h"
#include "LtdComplexComponent.h"
#include <variant>

//==============================================================================

class NoiseSectionEditor	: public LtdComplexComponent
{
public:
	//==============================================================================
    NoiseSectionEditor(LittleTeknoDrummerAudioProcessor&, 
		               int,  
		               int, 
		               std::string, 
		               Colour);

    ~NoiseSectionEditor();

private:
	//==============================================================================
	LittleTeknoDrummerLookAndFeel lookAndFeel;

	//==============================================================================
	LtdRotarySlider filterCutoffSlider{ juce::String("Cutoff")  };
	LtdRotarySlider filterResonanceSlider{ juce::String("Res") };
	LtdRotarySlider attackSlider{ juce::String("Attack") };
	LtdRotarySlider decaySlider{ juce::String("Decay") };

	//==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NoiseSectionEditor)
};
