#include <iostream>
#include <thread>
#include "windows.h"
#include <conio.h>
#include <stdio.h>
#include <mutex>
using namespace std;

struct letter_stack
    {
    int symbol;
    letter_stack* link_front;
    };
typedef letter_stack *Pletter_stack;

template <typename new_type> class stacker
    {
    private:
        Pletter_stack Header;
        Pletter_stack link_front;
        std::mutex locker;

    public:
        stacker ()
            {
            Pletter_stack Header = new letter_stack;
            Header -> link_front = nullptr;
            Header -> symbol = '\0';

            Pletter_stack link_front = Header;

            std::cout << "created" << std::endl;
            }

        ~stacker ()
            {
            std::cout << "deleted" << std::endl;
            }

        bool push_Front (new_type value)
            {
            std::cout << "puF_try" << std::endl;

            locker.lock ();

            Pletter_stack link_tmp = new letter_stack;

            link_front -> link_front = link_tmp;

            link_tmp -> link_front = nullptr;

            //link_front = link_front -> link_front;

            link_front = link_tmp;

            link_front -> symbol = (int)value;

            link_tmp = nullptr;

            delete link_tmp;

            locker.unlock ();

            return true;
            }


        bool pop_Front ()
            {
            std::cout << "poF_try" << std::endl;

            locker.lock ();

            if (!check_end)
                {
                Pletter_stack link_tmp = Header;

                while (link_tmp -> link_front -> link_front != nullptr)
                    {
                    link_tmp = link_tmp -> link_front;
                    }

                link_front = link_tmp;

                delete link_tmp -> link_front;

                link_tmp = nullptr;

                delete link_tmp;

                locker.unlock ();

                return true;
                }
            else
                {
                locker.unlock ();

                return false;
                }
            }


        int ret_Front ()
            {
            std::cout << "rf_try" << std::endl;

            return (int) link_front -> symbol;
            }

        bool check_end ()
            {
            if (Header == link_front)
                {
                std::cout << "true";

                Sleep (50);

                return true;
                }
            else
                {
                std::cout << "false";

                return false;
                }
            }

    };
