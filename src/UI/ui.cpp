#include <stdio.h>

#include <log_c/log.h>


#include <raylib.h>
#include <raymath.h>
#include <rlImGui.h>
#include <imgui.h>



#include "../ui_entry.hpp"
#include "ui.hpp"
#include "ui_helpers.cpp"
#include "layouts.h"

#include "../etk_tests.hpp"




static int selected_component = 1;
static bool loop_test = true;
static bool manual_test = false;



void etkUI::RenderUI()
{
    ImGui::PushFont(etkUI::FONT_TomorrowMedium);
    ImGui::SetNextWindowSizeConstraints(ImVec2(500, 500), ImVec2(FLT_MAX, FLT_MAX));
    if(ImGui::Begin("ETK", nullptr))
	{
        ImGui::PopFont();

        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(8, 10));
        
        if(ImGui::Button(ICON_FA_CIRCLE_PLAY, ImVec2(40, 40)))
        {
            log_debug("Running Test...");
        }

        ImGui::SameLine();

        if(ImGui::Button(ICON_FA_CIRCLE_PAUSE, ImVec2(40, 40)))
        {
            log_debug("Pausing Test...");
        }

        ImGui::PopStyleVar();

        ImGui::SameLine();

        ImGui::PushFont(etkUI::FONT_TomorrowMedium);

        ImGui::Checkbox("Continuitate", &loop_test);

        ImGui::SameLine();

        ImGui::Checkbox("Control Manual", &manual_test);

        ImGui::Separator();

		//ImGui::TextUnformatted(ICON_FA_CIRCLE_QUESTION);
        if(ImGui::BeginTabBar("MainTabBar", 0))
        {
            if(ImGui::BeginTabItem("Componente"))
            {
                ImGuiWindowFlags window_list_flags = ImGuiWindowFlags_HorizontalScrollbar;
            
                ImGui::BeginChild("InnerWindowList", ImVec2(ImGui::GetContentRegionAvail().x * ETK_WINDOW_LIST_WIDTH, 0), ImGuiChildFlags_None, window_list_flags);
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

                ImGui::EndChild();

                ImGui::SameLine();

                ImGuiWindowFlags ctrl_window_flags = ImGuiWindowFlags_None;
                ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
                ImGui::BeginChild("ControlsWindow", ImVec2(0, 0), ImGuiChildFlags_Borders, ctrl_window_flags);


                if(selected_component == etkTests::CT_SERVO)
                {
                    ImGui::Text("Page 1");
                }
                else if(selected_component == etkTests::CT_STEPPER)
                {
                    ImGui::Text("Page 2");
                }
                else if(selected_component == etkTests::CT_H_BRIDGE_L298N)
                {
                    ImGui::Text("Page 3");
                }
                else if(selected_component == etkTests::CT_DHT)
                {
                    ImGui::Text("Page 4");
                }
                else if(selected_component == etkTests::CT_LCD_I2C)
                {
                    ImGui::Text("Page 5");
                }
                else if(selected_component == etkTests::CT_LCD)
                {
                    ImGui::Text("Page 6");
                }
                else if(selected_component == etkTests::CT_OLED)
                {
                    ImGui::Text("Page 7");
                }
                else if(selected_component == etkTests::CT_TFT)
                {
                    ImGui::Text("Page 8");
                }
                else if(selected_component == etkTests::CT_SEVEN_SEG_DISPLAY)
                {
                    ImGui::Text("Page 9");
                }
                else if(selected_component == etkTests::CT_MPU6050)
                {
                    ImGui::Text("Page 10");
                }
                else if(selected_component == etkTests::CT_ULTRASONIC_HC06)
                {
                    ImGui::Text("Page 11");
                }
                else if(selected_component == etkTests::CT_KEYPAD_2X4)
                {
                    ImGui::Text("Page 12");
                }
                else if(selected_component == etkTests::CT_KEYPAD_4X4)
                {
                    ImGui::Text("Page 13");
                }
                else if(selected_component == etkTests::CT_KEYPAD_3X4)
                {
                    ImGui::Text("Page 14");
                }
                else if(selected_component == etkTests::CT_INFRARED)
                {
                    ImGui::Text("Page 15");
                }
                else if(selected_component == etkTests::CT_LED_MATRIX)
                {
                    ImGui::Text("Page 16");
                }
                else if(selected_component == etkTests::CT_WATER_LEVEL)
                {
                    ImGui::Text("Page 17");
                }
                else if(selected_component == etkTests::CT_SOIL_MOISTURE)
                {
                    ImGui::Text("Page 18");
                }
                else if(selected_component == etkTests::CT_SPEED_SENSOR)
                {
                    ImGui::Text("Page 19");
                }
                else if(selected_component == etkTests::CT_GAS_SENSOR)
                {
                    ImGui::Text("Page 20");
                }
                else if(selected_component == etkTests::CT_SMOKE_DETECTOR)
                {
                    ImGui::Text("Page 21");
                }
                else if(selected_component == etkTests::CT_MICROPHONE)
                {
                    ImGui::Text("Page 22");
                }
                else if(selected_component == etkTests::CT_PH_METER)
                {
                    ImGui::Text("Page 23");
                }
                else if(selected_component == etkTests::CT_HALL_SENSOR)
                {
                    ImGui::Text("Page 24");
                }
                else if(selected_component == etkTests::CT_FLOW_METER)
                {
                    ImGui::Text("Page 25");
                }
                else if(selected_component == etkTests::CT_POTENTIOMETER)
                {
                    ImGui::Text("Page 26");
                }
                else if(selected_component == etkTests::CT_PHOTORESISTOR)
                {
                    ImGui::Text("Page 27");
                }
                else if(selected_component == etkTests::CT_STEPPER_MOTOR_ULN2003)
                {
                    ImGui::Text("Page 28");
                }
                else if(selected_component == etkTests::CT_RFID_RC522)
                {
                    ImGui::Text("Page 29");
                }
                else if(selected_component == etkTests::CT_JOYSTICK_X2)
                {
                    ImGui::Text("Page 30");
                }
                else if(selected_component == etkTests::CT_IR_REMOTE)
                {
                    ImGui::Text("Page 31");
                }
                else if(selected_component == etkTests::CT_PCA9685)
                {
                    ImGui::Text("Page 32");
                }
                else if(selected_component == etkTests::CT_A4988_DRIVER)
                {
                    ImGui::Text("Page 33");
                }
                else if(selected_component == etkTests::CT_RT_CLOCK_DS1302)
                {
                    ImGui::Text("Page 34");
                }
                else if(selected_component == etkTests::CT_RT_CLOCK_DS3231)
                {
                    ImGui::Text("Page 35");
                }
                else if(selected_component == etkTests::CT_RT_CLOCK_DS1307)
                {
                    ImGui::Text("Page 36");
                }
                else if(selected_component == etkTests::CT_TTP229)
                {
                    ImGui::Text("Page 37");
                }
                else if(selected_component == etkTests::CT_ARDUINO_UNO)
                {
                    ImGui::Text("Page 38");
                }
                else if(selected_component == etkTests::CT_ARDUINO_MEGA)
                {
                    ImGui::Text("Page 39");
                }
                else if(selected_component == etkTests::CT_ARDUINO_NANO)
                {
                    ImGui::Text("Page 40");
                }
                else if(selected_component == etkTests::CT_ARDUINO_GIGA)
                {
                    ImGui::Text("Page 41");
                }
                else if(selected_component == etkTests::CT_RESISTOR)
                {
                    ImGui::Text("Page 42");
                }
                else if(selected_component == etkTests::CT_TB6600)
                {
                    ImGui::Text("Page 43");
                }
                
                
                ImGui::EndChild();
                ImGui::PopStyleVar();


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
    ImGui::PopFont();
}