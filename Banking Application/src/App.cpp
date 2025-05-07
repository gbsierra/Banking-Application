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
    static bool remove_account_window = false;   // Remove Account Window

    static std::string name = "Bank Teller";     // Bank Teller Name

    // Bank Data
    Bank myBank("src/BankData.txt");           // populate myBank with accounts
    std::string accounts = myBank.printVector(); // string version of BankData
    std::string sorted_accounts = myBank.printSortedSavings();
    std::string deposits = myBank.printDeposits();
    std::string withdrawals = myBank.printWithdrawals();

    int accId;

    bool testing = false; //if true, displays BankData list in terminal on launch

    // Renders Main Header
    void RenderApplicationHeader() {

        // Set the header position at the top of the screen
        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, 50));
        ImGui::SetNextWindowBgAlpha(0.9f);
        //ImGui::SetNextWindowFocus();
        ImGui::Begin("HeaderWindow", NULL, ImGuiWindowFlags_NoDecoration );

        // Application name
        ImGui::SetWindowFontScale(1.4f);
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);
        ImGui::Text("  Banking Application");

        // Add minimize and close buttons, aligned to the right
        ImGui::SameLine(ImGui::GetWindowWidth() - 65);
        if (ImGui::Button("-")) {
            HWND activeWindow = GetForegroundWindow(); // Get the currently active window
            PostMessage(activeWindow, WM_SYSCOMMAND, SC_MINIMIZE, 0); // Minimize the active window

        }
        ImGui::SameLine();
        if (ImGui::Button("x")) {
            PostQuitMessage(0); // Close the application
        }

        ImGui::End();
    }
    
    // Renders Main Window
    void RenderApplicationWindow() {
        ImGui::GetStyle().WindowRounding = 0.0f;
        ImGui::SetNextWindowPos(ImVec2(0.0f, 50.0f), ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(800.0f, 600.0f), ImGuiCond_Always);

        ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.2f, 0.2f, 0.2f, 0.8f));
        ImGui::Begin("Banking Application", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);        

        RenderApplicationHeader();

        ImGui::SetCursorPosX(543);
        ImGui::Separator();

        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 6);
        ImGui::SetCursorPosX(565);
        if (ImGui::Button("Manage Customer Funds", ImVec2(200, 50))) {
            manage_funds_window = true;
        }
        if (ImGui::IsItemHovered()) {
            ImGui::BeginTooltip();
            ImGui::SeparatorText("Please have:");
            ImGui::Bullet();
            ImGui::Text("First and Last Name");
            ImGui::Bullet();
            ImGui::Text("Account Number");
            ImGui::Separator();
            ImGui::Text("Ready from client");
            ImGui::EndTooltip();
        }
        ImGui::SetCursorPosX(565);
        if (ImGui::Button("Create Customer Account", ImVec2(200, 50))) {
            create_account_window = true;
        }
        if (ImGui::IsItemHovered()) {
            ImGui::BeginTooltip();
            ImGui::SeparatorText("Please have:");
            ImGui::Bullet();
            ImGui::Text("First and Last Name");
            ImGui::Bullet();
            ImGui::Text("New Id");
            ImGui::Bullet();
            ImGui::Text("New Account Number");
            ImGui::Separator();
            ImGui::Text("Ready for system");
            ImGui::EndTooltip();
        }
        ImGui::SetCursorPosX(565);
        if (ImGui::Button("Remove Customer Account", ImVec2(200, 50))) {
            remove_account_window = true;
        }
        if (ImGui::IsItemHovered()) {
            ImGui::BeginTooltip();
            ImGui::SeparatorText("Please have:");
            ImGui::Bullet();
            ImGui::Text("Account Id");
            ImGui::Separator();
            ImGui::Text("Ready from client");
            ImGui::EndTooltip();
        }
        //ImGui::SetCursorPosX(565);
        //if (ImGui::Button("Future Button2", ImVec2(200, 50))) {
        //}
        //if (ImGui::IsItemHovered()) {
         //   ImGui::BeginTooltip();
         //   ImGui::Text("test message");
         //   ImGui::EndTooltip();
        //}

        ImGui::SetCursorPosX(543);
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);
        ImGui::Separator();

        if (testing) {
            OpenTerminal([]() {std::cout << accounts << std::endl;}, true);
            testing = false;
        }

        ImGui::End();
        ImGui::PopStyleColor();
    }
    
    // Renders Manage Customer Funds Window
    static void RenderManageCustomerFundsWindow() {
        if (manage_funds_window) {
            ImGui::SetNextWindowPos(ImVec2(275, 163));
            ImGui::SetNextWindowSize(ImVec2(226, 64));
            ImGui::Begin("Manage Customer Funds", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove);

            // Withdraw Button
            if (ImGui::Button("Withdraw")) {
                OpenTerminal([]() {myBank.withdraw();}, true);
                manage_funds_window = false;
            }
            ImGui::SameLine();
            // Deposit Button
            if (ImGui::Button("Deposit")) {
                OpenTerminal([]() {myBank.deposit();}, true);
                manage_funds_window = false;
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
    static void RenderCreateCustomerAccountWindow() {
        if (create_account_window) {
            ImGui::SetNextWindowPos(ImVec2(261, 215));
            ImGui::SetNextWindowSize(ImVec2(228, 95));
            ImGui::Begin("Add New Customer Account", nullptr, ImGuiWindowFlags_NoCollapse);
            OpenTerminal([]() {myBank.addAccount();}, true);

            create_account_window = false;
            ImGui::End();
        }
    }
    
    // Renders Remove Customer Account Window
    static void RenderRemoveCustomerAccountWindow() {
        if (remove_account_window) {
            ImGui::OpenPopup("Remove Customer Account");
            remove_account_window = false;
        }

        ImGui::GetStyle().WindowRounding = 10.0f;
        ImGui::SetNextWindowPos(ImVec2(279, 244), ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(255, 132), ImGuiCond_Always);

        if (ImGui::BeginPopupModal("Remove Customer Account", nullptr, ImGuiWindowFlags_NoCollapse)) {
            ImGui::InputInt("Account Id", &accId, 0, 0, ImGuiInputTextFlags_CharsDecimal);

            if (accId < 100000 || accId > 999999) {
                ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Please enter a 6-digit account ID.");
            }

            int temp = accId;

            if (ImGui::Button("Confirm", ImVec2(135, 40))) {
                if (!(temp < 100000 || temp > 999999)) {
                    OpenTerminal([temp]() { myBank.removeAccount(temp); }, true);
                    accId = 0;
                    ImGui::CloseCurrentPopup();
                }
            }
            ImGui::SameLine();
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);
            if (ImGui::Button("Cancel", ImVec2(80, 30))) {
                ImGui::CloseCurrentPopup();
            }

            ImGui::EndPopup();
        }
    }

    
    // Renders Welcome Window
    static void RenderWelcomeWindow() {
        ImGui::SetNextWindowPos(ImVec2(541, 526));
        ImGui::SetNextWindowSize(ImVec2(248, 110));
        ImGui::Begin("Welcome", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar);
        std::string welcome = "Welcome, " + name;
        ImGui::SeparatorText(welcome.c_str());
        ImGui::Separator();
        ImGui::Text("Recent application updates:");
        ImGui::Bullet();
        ImGui::Text("account list window");
        ImGui::Bullet();
        ImGui::Text("savings account list, sorted");
        ImGui::Bullet();
        ImGui::Text("create/remove account");
        ImGui::Bullet();
        ImGui::Text("updated styling");
        ImGui::Bullet();
        ImGui::Text("new withdraws/deposits list");
        ImGui::Bullet();
        ImGui::Text("added savings/checking");


        //ImGui::ShowDemoWindow(&show_demo_window);

        ImGui::End();
    }
    
    // Renders Customer List Window
    static void RenderCustomerListWindow() {
        ImGui::GetStyle().WindowRounding = 10.0f;
        ImGui::SetNextWindowPos(ImVec2(6, 57));
        ImGui::SetNextWindowSize(ImVec2(226, 583));
        ImGui::Begin("Account List:", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBackground);

        if (accounts.empty()) {
            ImGui::Text("No accounts available.");
        }
        else {
            ImGui::SetWindowFontScale(0.865f);
            ImGui::Text("%s", accounts.c_str());
        }

        ImGui::End();
    }
    
    // Renders List Window 1 (sorted descending)
    static void RenderList1Window() {
        ImGui::SetNextWindowPos(ImVec2(240, 58));
        ImGui::SetNextWindowSize(ImVec2(298, 196));
        ImGui::Begin("Highest Savings Balances:", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBackground);

        ImGui::GetStyle().WindowRounding = 10.0f;
        ImGui::SetWindowFontScale(0.865f);
        ImGui::Text("%s", sorted_accounts.c_str());


        ImGui::End();
    }
    
    // Renders List Window 2 (recent withdrawals)
    static void RenderList2Window() {
        ImGui::SetNextWindowPos(ImVec2(240, 258));
        ImGui::SetNextWindowSize(ImVec2(298, 196));
        ImGui::Begin("Recent Withdrawals:", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBackground);

        ImGui::GetStyle().WindowRounding = 10.0f;
        ImGui::SetWindowFontScale(0.865f);
        ImGui::Text("%s", withdrawals.c_str());

        ImGui::End();
    }
    
    // Renders List Window 3 (recent deposits)
    static void RenderList3Window() {
        ImGui::SetNextWindowPos(ImVec2(240, 456));
        ImGui::SetNextWindowSize(ImVec2(298, 196));
        ImGui::Begin("Recent Deposits:", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBackground);

        ImGui::GetStyle().WindowRounding = 10.0f;
        ImGui::SetWindowFontScale(0.865f);
        ImGui::Text("%s", deposits.c_str());

        ImGui::End();
    }
    
    // Main Render Function for UI
    void RenderUI() {
        RenderApplicationWindow();
        RenderManageCustomerFundsWindow();
        RenderCreateCustomerAccountWindow();
        RenderRemoveCustomerAccountWindow();
        RenderCustomerListWindow();
        RenderList1Window();
        RenderList2Window();
        RenderList3Window();

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

        accounts = myBank.printVector(); //update strings 
        sorted_accounts = myBank.printSortedSavings();
        deposits = myBank.printDeposits();
        withdrawals = myBank.printWithdrawals();
    }
}