#include <iostream>
#include <thread>
#include "windows.h"
#include <conio.h>
#include <stdio.h>
#include <mutex>
#pragma once
using namespace std;

#define development_stack FALSE

struct letter_stack
    {
    int symbol;
    letter_stack* link_back;
    };
typedef letter_stack *Pletter_stack;


template <typename l_type> class stacker
    {
    private:
        Pletter_stack Header;

        std::mutex locker;

    public:
        stacker ()
            {
            Header = nullptr;

            #if development_stack
            std::cout << "created" << std::endl;
            #endif
            }

        ~stacker ()
            {
            #if development_stack
            std::cout << std::endl;
            std::cout << "deleted" << std::endl;
            #endif
            }

        bool push_Front (l_type value)
            {
            #if development_stack
            std::cout << "from class_" << value << "__" << std::endl;
            #endif

            locker.lock ();

            Pletter_stack link_tmp = new letter_stack;

            link_tmp -> link_back = Header;

            link_tmp -> symbol = value;

            Header = link_tmp;

            link_tmp = nullptr;

            locker.unlock ();

            return true;
            }

        bool pop_Front ()
            {
            #if development_stack
            std::cout << "poF_try" << std::endl;
            #endif

            locker.lock ();

            if (!check_end ())
                {
                Pletter_stack link_tmp = Header;

                Header = Header -> link_back;

                delete link_tmp;

                locker.unlock ();
                }
            else
                {
                locker.unlock ();

                return false;
                }
            }


        int ret_Front ()
            {
            if (!check_end())
               {
               return (int) Header -> symbol;
               }
            }


        bool check_end ()
            {
            if (Header == nullptr)
                {
                #if development_stack
                std::cout << "";
                #endif

                return true;
                }
            else
                {
                #if development_stack
                std::cout << "false";
                #endif

                return false;
                }
            }

    };


