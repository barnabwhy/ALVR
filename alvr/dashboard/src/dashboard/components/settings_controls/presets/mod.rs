mod higher_order_choice;
mod mirror;

pub mod builtin_schema;
pub mod schema;

use self::schema::PresetSchema;
use alvr_packets::PathValuePair;
use eframe::egui::Ui;
use serde_json as json;

pub enum PresetControl {
    HigherOrderChoice(higher_order_choice::Control),
    // Mirror(...)
}

impl PresetControl {
    pub fn new(schema: PresetSchema) -> Self {
        match schema {
            PresetSchema::Choice(schema) => {
                Self::HigherOrderChoice(higher_order_choice::Control::new(schema))
            }
            PresetSchema::Mirror(_) => unimplemented!(),
            PresetSchema::GameAudioPlaceholder => todo!(),
            PresetSchema::MicrophonePlaceholder => todo!(),
            
        }
    }

    pub fn update_session_settings(&mut self, session_settings_json: &json::Value) {
        match self {
            Self::HigherOrderChoice(control) => {
                control.update_session_settings(session_settings_json)
            }
        }
    }

    pub fn ui(&mut self, ui: &mut Ui) -> Vec<PathValuePair> {
        match self {
            Self::HigherOrderChoice(control) => control.ui(ui),
        }
    }
}

pub struct PresetEntry {}
