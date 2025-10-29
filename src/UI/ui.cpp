#include <raylib.h>
#include <raymath.h>
#include <rlImGui.h>
#include <imgui.h>




#include "ui.hpp"
#include "ui_helpers.cpp"

#include "../etk_tests.hpp"




static int selected_component = 1;



void etkUI::RenderUI()
{
    ImGui::SetNextWindowSizeConstraints(ImVec2(500, 500), ImVec2(FLT_MAX, FLT_MAX));
    if(ImGui::Begin("ETK", nullptr))
	{
		//ImGui::TextUnformatted(ICON_FA_CIRCLE_QUESTION);
        if(ImGui::BeginTabBar("MyTabBar", 0))
        {
            if(ImGui::BeginTabItem("Componente"))
            {
                // MARK: component list
                if(ImGui::CollapsingHeader("Microcontrolere și plarforme", ImGuiTreeNodeFlags_None))
                {
                    ui_helpers::RenderSelectable("Arduino UNO",  selected_component, etkTests::CT_ARDUINO_UNO);
                    ui_helpers::RenderSelectable("Arduino Nano", selected_component, etkTests::CT_ARDUINO_NANO);
                    ui_helpers::RenderSelectable("Arduino Mega", selected_component, etkTests::CT_ARDUINO_MEGA);
                    ui_helpers::RenderSelectable("Arduino Giga", selected_component, etkTests::CT_ARDUINO_GIGA);
                }

                if(ImGui::CollapsingHeader("Module de extensie", ImGuiTreeNodeFlags_None))
                {
                    ui_helpers::RenderSelectable("nolst",  selected_component, 775);
                }

                if(ImGui::CollapsingHeader("Display-uri", ImGuiTreeNodeFlags_None))
                {
                    ui_helpers::RenderSelectable("LCD I2C",                       selected_component, etkTests::CT_LCD_I2C);
                    ui_helpers::RenderSelectable("LCD",                           selected_component, etkTests::CT_LCD);
                    ui_helpers::RenderSelectable("OLED",                          selected_component, etkTests::CT_OLED);
                    ui_helpers::RenderSelectable("TFT",                           selected_component, etkTests::CT_TFT);
                    ui_helpers::RenderSelectable("Display numeric cu 7 segmente", selected_component, etkTests::CT_SEVEN_SEG_DISPLAY);
                }

                if(ImGui::CollapsingHeader("Senzori Analogici / Digitali", ImGuiTreeNodeFlags_None))
                {
                    ui_helpers::RenderSelectable("Senzor de distanță HC06",   selected_component, etkTests::CT_ULTRASONIC_HC06);
                    ui_helpers::RenderSelectable("Receptor infraroșu",        selected_component, etkTests::CT_INFRARED);
                    ui_helpers::RenderSelectable("DHT",                       selected_component, etkTests::CT_DHT);
                    ui_helpers::RenderSelectable("Detector de gaz",           selected_component, etkTests::CT_GAS_SENSOR);
                    ui_helpers::RenderSelectable("Detector de fum",           selected_component, etkTests::CT_SMOKE_DETECTOR);
                    ui_helpers::RenderSelectable("Nivel de apă",              selected_component, etkTests::CT_WATER_LEVEL);
                    ui_helpers::RenderSelectable("Umiditate Sol",             selected_component, etkTests::CT_SOIL_MOISTURE);
                    ui_helpers::RenderSelectable("Senzor de rotații",         selected_component, etkTests::CT_SPEED_SENSOR);
                    ui_helpers::RenderSelectable("Senzor Giroscopic MPU6050", selected_component, etkTests::CT_MPU6050);
                    ui_helpers::RenderSelectable("Senzor de Viteză",          selected_component, 500);
                    ui_helpers::RenderSelectable("Microfon",                  selected_component, etkTests::CT_MICROPHONE);
                }

                if(ImGui::CollapsingHeader("Motoare", ImGuiTreeNodeFlags_None))
                {
                    ui_helpers::RenderSelectable("Servo",                   selected_component, etkTests::CT_SERVO);
                    ui_helpers::RenderSelectable("Stepper ULN2003",         selected_component, etkTests::CT_STEPPER_MOTOR_ULN2003);
                    ui_helpers::RenderSelectable("Stepper A4988 / DRV8825", selected_component, etkTests::CT_A4988_DRIVER);
                    ui_helpers::RenderSelectable("TB 6600",                 selected_component, etkTests::CT_TB6600);
                    ui_helpers::RenderSelectable("Punte H L298N",           selected_component, etkTests::CT_H_BRIDGE_L298N);
                    ui_helpers::RenderSelectable("Servo PCA9685",           selected_component, etkTests::CT_PCA9685);
                }

                if(ImGui::CollapsingHeader("Alimentare și control voltaj / tensiune", ImGuiTreeNodeFlags_None))
                {
                    ui_helpers::RenderSelectable("nolst",  selected_component, 8832);
                }

                if(ImGui::CollapsingHeader("Comunicare și rețea", ImGuiTreeNodeFlags_None))
                {
                    ui_helpers::RenderSelectable("nolst",  selected_component, 648);
                }

                if(ImGui::CollapsingHeader("Interfețe", ImGuiTreeNodeFlags_None))
                {
                    ui_helpers::RenderSelectable("nolst",  selected_component, 432);
                }

                if(ImGui::CollapsingHeader("Componente Pasive", ImGuiTreeNodeFlags_None))
                {
                    ui_helpers::RenderSelectable("Modul Tastatură",        selected_component, 550);
                    ui_helpers::RenderSelectable("Potențiometru",          selected_component, etkTests::CT_POTENTIOMETER);
                    ui_helpers::RenderSelectable("Modul joystick (2 axe)", selected_component, etkTests::CT_JOYSTICK_X2);
                    ui_helpers::RenderSelectable("Senzor debit apă",       selected_component, etkTests::CT_FLOW_METER);
                    ui_helpers::RenderSelectable("Fotorezitsor",           selected_component, etkTests::CT_PHOTORESISTOR);
                    ui_helpers::RenderSelectable("Senzor magnetic (Hall)", selected_component, etkTests::CT_HALL_SENSOR);
                    ui_helpers::RenderSelectable("Buzzer",                 selected_component, 505);
                }
                ImGui::EndTabItem();
            }
            if(ImGui::BeginTabItem("Valori"))
            {
                ImGui::Text("- - - - Implot - - - -");
                ImGui::EndTabItem();
            }
            if(ImGui::BeginTabItem("Setări"))
            {
                ImGui::Text("eeeee");
                ImGui::EndTabItem();
            }
            ImGui::EndTabBar();
        }
	}
    ImGui::End();
}