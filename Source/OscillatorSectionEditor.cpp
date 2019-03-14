/*
  ==============================================================================

    OscillatorSectionEditor.cpp
    Created: 6 Nov 2018 2:36:24pm
    Author:  dfila

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "OscillatorSectionEditor.h"

//==============================================================================
OscillatorSectionEditor::OscillatorSectionEditor (LittleTeknoDrummerAudioProcessor& p, 
	                                              int nRows, int nCols, 
	                                              std::string title) 
	: LtdComplexComponent(p, nRows, nCols, title)
{
	setLookAndFeel(&lookAndFeel);

	controls = 
	{ 
		{ &m_oscSlider,            "WAVE-TYPE"},
		{ &m_freqSlider,           "FREQ"},
		{ &m_attackSlider ,        "ATTACK"},
		{ &m_decaySlider,          "DECAY" },
		{ &m_pitchEnvAmountSlider, "PITCH-ENV-AMOUNT" },
		{ &m_pitchEnvRateSlider,   "PITCH-ENV-RATE" },
		{ &m_pitchLfoAmountSlider, "PITCH-LFO-AMOUNT" },
		{ &m_pitchLfoRateSlider,   "PITCH-LFO-RATE" } 
	};

	setupChildren();
}

OscillatorSectionEditor::~OscillatorSectionEditor()
{
	setLookAndFeel(nullptr);
}