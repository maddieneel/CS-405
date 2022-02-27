// Exceptions.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

//defining new custom exception
struct customException : public std::exception {
    const char* what() const throw() {
        return "Custom Exception";
    }
};

bool do_even_more_custom_application_logic()
{
    // TODO: Throw any standard exception
    throw std::bad_exception(); //handle unexpected exceptions

    std::cout << "Running Even More Custom Application Logic." << std::endl;

    return true;
}
void do_custom_application_logic()
{
    // TODO: Wrap the call to do_even_more_custom_application_logic()
    //  with an exception handler that catches std::exception, displays
    //  a message and the exception.what(), then continues processing
    std::cout << "Running Custom Application Logic." << std::endl;

    try { //wrap and try 
        if (do_even_more_custom_application_logic())
        {
            std::cout << "Even More Custom Application Logic Succeeded." << std::endl;
        }
    }

    catch(std::exception exception) { //catch exception
        std::cerr << "Exception Caught: " << exception.what() << std::endl; //display a message and identify exception
    }

    // TODO: Throw a custom exception derived from std::exception
    //  and catch it explictly in main
    throw customException(); //custom exception defined at top

    std::cout << "Leaving Custom Application Logic." << std::endl;

}

float divide(float num, float den)
{
    // TODO: Throw an exception to deal with divide by zero errors using
    //  a standard C++ defined exception
    
    if (den == 0) { //if the denominator is 0
        throw std::runtime_error("Can not be divided by zero"); //throw exception runtime_error due to the inability to detect error while reviewing code
    }
    return (num / den);
}

void do_division() noexcept
{
    //  TODO: create an exception handler to capture ONLY the exception thrown
    //  by divide.

    float numerator = 10.0f;
    float denominator = 0;

    try {
        auto result = divide(numerator, denominator);
        std::cout << "divide(" << numerator << ", " << denominator << ") = " << result << std::endl;
    }
    catch(std::exception exception) { //catch exception
        std::cerr << "Exception Caught: " << exception.what() << std::endl; ///display a message and identify exception - should call divide runtime error
    }
}

int main()
{
    try { //try exception tests
        std::cout << "Exceptions Tests!" << std::endl;
        do_division();
        do_custom_application_logic();
    }

    // TODO: Create exception handlers that catch (in this order):
    //  your custom exception
    // std::exception
    // uncaught exception
    // that wraps the whole main function, and displays a message to the console.
    
    //your custom exception
    catch (customException exception) {
        std::cerr << "Exception Caught: " << exception.what() << std::endl;
    }

    //  std::exception
    catch (std::exception exception) {
        std::cerr << "Exception Caught: " << exception.what() << std::endl;
    }

    //  uncaught exception 
    catch(...){
        std::cerr << "Unexpected Exception Caught" << std::endl;
    }

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu