#ifndef __WYOOS_DRIVERS_DRIVER_H
#define __WYOOS_DRIVERS_DRIVER_H

namespace wyoos
{
    namespace drivers
    {

        class Driver
        {
        public:
            Driver();
            ~Driver();

            virtual void Activate();
            virtual int Reset();
            virtual void Deactivate();
        };

        class DriverManager
        {
        protected:
            Driver* drivers[256];
            int numDrivers;

        public:
            DriverManager();
            void AddDriver(Driver*);
            void ActivateAll();
        };

    }
}

#endif 