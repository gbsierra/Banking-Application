#include "App.h"

#include "Bank.h"

#include "imgui.h"
#include <string>
#include <memory>
#include <iostream>
#include <cstdlib>
#include <Windows.h>


// App Namespace for imgui implementation
namespace App {

    // Declarations
    static bool manage_funds_window = false;     // Manage Funds Window
    static bool create_account_window = false;   // Create Account Window

    static std::string name = "Bank Teller";     // Bank Teller Name

    // Bank
    Bank myBank("imgui/BankData.txt");           // populate myBank with accounts
    std::string accounts = myBank.printVector(); // string version of BankData

    bool testing = false; //if true, displays BankData list in terminal on launch


    // Renders Main Window
    void RenderApplicationWindow() {
        ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f), ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(800.0f, 600.0f), ImGuiCond_Always);

        ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.5f, 0.5f, 0.5f, 0.70f));

        ImGui::Begin("Banking Application", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar);        float windowWidth = ImGui::GetContentRegionAvail().x;

        ImGui::SetCursorPosX(580);
        ImGui::Text("Options:");

        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 6);

        ImGui::SetCursorPosX(520);
        if (ImGui::Button("Manage Customer Funds", ImVec2(200, 50))) {
            manage_funds_window = true;
        }

        ImGui::SetCursorPosX(520);
        if (ImGui::Button("Create Customer Account", ImVec2(200, 50))) {
            create_account_window = true;
        }


        if (testing) {
            OpenTerminal([]() {std::cout << accounts << std::endl;}, true);
            testing = false;
        }


        ImGui::End();
        ImGui::PopStyleColor();
    }
    // Renders Manage Customer Funds Window
    static void RenderManageCustomerFunds() {
        if (manage_funds_window) {
            ImGui::Begin("Manage Customer Funds", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove);

            // Withdraw Button
            if (ImGui::Button("Withdraw")) {
                OpenTerminal([]() {myBank.withdraw();}, false);

            }
            ImGui::SameLine();
            // Deposit Button
            if (ImGui::Button("Deposit")) {
                OpenTerminal([]() {myBank.deposit();}, false);
            }
            ImGui::SameLine();
            // Cancel Button
            if (ImGui::Button("Cancel")) {
                manage_funds_window = false;
            }

            ImGui::End();
        }
    } 
    // Renders Create Customer Account Window
    static void RenderCreateCustomerAccount() {
        if (create_account_window) {
            ImGui::Begin("Add New Customer Account", nullptr, ImGuiWindowFlags_NoCollapse);
            OpenTerminal([]() {myBank.addAccount();}, true);

            create_account_window = false;
            ImGui::End();
        }
    }
    // Renders Welcome Window
    static void RenderWelcomeWindow() {
        ImGui::Begin("Welcome", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBackground);
        ImGui::Text("Welcome, %s", name.c_str());
        ImGui::NewLine();
        ImGui::Text("Recent application updates:");
        ImGui::Bullet();
        ImGui::Text("new banking window");
        ImGui::Bullet();
        ImGui::Text("new account list");
        ImGui::Bullet();
        ImGui::Text("create account function");
        ImGui::Bullet();
        ImGui::Text("updated styling");


        //ImGui::ShowDemoWindow(&show_demo_window);

        ImGui::End();
    }
    // Renders Customer List Window
    static void RenderCustomerListWindow() {
        ImGui::Begin("Account List:", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBackground);

        if (accounts.empty()) {
            ImGui::Text("No accounts available.");
        }
        else {
            ImGui::GetStyle().WindowRounding = 10.0f;
            ImGui::SetWindowFontScale(0.865f);
            ImGui::Text("%s", accounts.c_str());
        }

        ImGui::End();
    }
    
    // Main Render Function for UI
    void RenderUI() {
        RenderApplicationWindow();
        RenderManageCustomerFunds();
        RenderCreateCustomerAccount();
        RenderCustomerListWindow();
        RenderWelcomeWindow();
    }

    // Open a terminal
    static void OpenTerminal(std::function<void()> command, bool wait) {
        AllocConsole(); //allocate console
        FILE* out;
        FILE* in;
        freopen_s(&out, "CONOUT$", "w", stdout); //redirect stdout to console
        freopen_s(&in, "CONIN$", "r", stdin);    //redirect stdin to console
        
        command();

        if(wait){
            std::cout << "Press Enter to continue..." << std::endl;
            std::cin.ignore(); 
            std::cin.get();
        }

        fclose(out);
        fclose(in);
        FreeConsole(); //free allocated console

        accounts = myBank.printVector(); //update string
    }
}