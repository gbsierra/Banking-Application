#pragma once
#include <functional>

namespace App {

    // Renders Main Applicatino Window
    static void RenderApplicationWindow();

    // Renders Manage Customer Funds Window
    static void RenderManageCustomerFundsWindow();

    // Renders Create Customer Account Window
    static void RenderCreateCustomerAccountWindow();

    // Renders Remove Customer Account Window
    static void RenderRemoveCustomerAccountWindow();

    // Renders Customer List Window
    static void RenderCustomerListWindow();

    // Renders List Window 1 (sorted descending)
    static void RenderList1Window();

    // Renders List Window 2 (recent withdrawals)
    static void RenderList2Window();

    // Renders List Window 3 (recent deposits)
    static void RenderList3Window();

    // Renders Welcome Window
    static void RenderWelcomeWindow();

    // Main Render Function for UI
    void RenderUI();


    // Open a terminal
    static void OpenTerminal(std::function<void()> command, bool wait);
}