#include <raylib.h>
#include <raymath.h>
#include <rlImGui.h>
#include <imgui.h>




#include "ui.hpp"





void etkUI::RenderUI()
{
    ImGui::SetNextWindowSizeConstraints(ImVec2(500, 500), ImVec2(FLT_MAX, FLT_MAX));
    //ImGui::SetNextWindowSize(ImVec2(800, 800));
    if(ImGui::Begin("ETK", nullptr))
	{
		//ImGui::TextUnformatted(ICON_FA_CIRCLE_QUESTION);
        if(ImGui::BeginTabBar("MyTabBar", 0))
        {
            if(ImGui::BeginTabItem("Componente"))
            {
                //ImGui::Text("6 7");
                if(ImGui::CollapsingHeader("Microcontrolere și plarforme", ImGuiTreeNodeFlags_None))
                {
                    //ImGui::Text("IsItemHovered: %d", ImGui::IsItemHovered());
                    //for (int i = 0; i < 5; i++)
                    //    ImGui::Text("Some content %d", i);

                    ImGui::Selectable("1. I am selectable", true);
                    ImGui::Selectable("2. I am selectable", false);
                    ImGui::Selectable("3. I am selectable", false);
                }

                if(ImGui::CollapsingHeader("Module de extensie", ImGuiTreeNodeFlags_None))
                {
                    ImGui::Text("dfkgjhdfgd");
                }

                if(ImGui::CollapsingHeader("Display-uri", ImGuiTreeNodeFlags_None))
                {
                    ImGui::Text("kgvjhdfg");
                }

                if(ImGui::CollapsingHeader("Senzori Analogici / Digitali", ImGuiTreeNodeFlags_None))
                {
                    ImGui::Text("gldfjghdfkgjh");
                }

                if(ImGui::CollapsingHeader("Motoare", ImGuiTreeNodeFlags_None))
                {
                    ImGui::Text("gvkjhfdgjkhdfg");
                }

                if(ImGui::CollapsingHeader("Alimentare și control voltaj / tensiune", ImGuiTreeNodeFlags_None))
                {
                    ImGui::Text("fkdjghfdjkghdfkg");
                }

                if(ImGui::CollapsingHeader("Comunicare și rețea", ImGuiTreeNodeFlags_None))
                {
                    ImGui::Text("dkfgjhdfgjkh");
                }

                if(ImGui::CollapsingHeader("Interfețe", ImGuiTreeNodeFlags_None))
                {
                    ImGui::Text("kljghfdkgjh");
                }

                if(ImGui::CollapsingHeader("Componente Pasive", ImGuiTreeNodeFlags_None))
                {
                    ImGui::Text("dfgljdhfgjk");
                }
                ImGui::EndTabItem();
            }
            if(ImGui::BeginTabItem("Valori"))
            {
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