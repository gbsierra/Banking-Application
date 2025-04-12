#pragma once
#include <functional>

namespace App {

    // Renders Main Applicatino Window
    static void RenderApplicationWindow();
    // Renders Manage Customer Funds Window
    static void RenderManageCustomerFunds();
    // Renders Create Customer Account Window
    static void RenderCreateCustomerAccount();
    // Renders Customer List Window
    static void RenderCustomerListWindow();
    // Renders Welcome Window
    static void RenderWelcomeWindow();

    // Open a terminal
    static void OpenTerminal(std::function<void()> command, bool wait);

    // Main Render Function for UI
    void RenderUI();
}