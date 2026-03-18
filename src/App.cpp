#include "App.h"

App *App::_instance = nullptr;
App::App() : _lcd(0x27, 16, 2),
             _display(_lcd),
             _menu("Main Menu"),
             _encoder(EN_CLK, EN_DT, EN_SW),
             _appMode(AppMode::HOME_SCREEN),
             _motorItem("Motor", App::onSetToggle),
             _heaterItem("Heater", App::onSetToggle),
             _setTempItem("Set Temp", App::onSetUpdateValue),
             _setSpeedItem("Set Speed", App::onSetUpdateValue),
             _tuningPIDItem("Tuning PID", App::onSetAction),
             _exitItem("Exit", App::onSetAction),
             _targetTemperature(0),
             _targetSpeed(0)
{
    _instance = this;
}

void App::handleUI()
{
    int32_t delta = _encoder.getDelta();
    if (delta != 0)
    {
        switch (_appMode)
        {
        case AppMode::HOME_SCREEN:
            if (_encoder.wasClicked())
            {
                _appMode = AppMode::MAIN_MENU;
            }
            break;
        case AppMode::MAIN_MENU:
            _menu.navigate(delta);
            if (_encoder.wasClicked())
            {
                _menu.select();
                if (_menu.getCurrentItem() == &_exitItem) _appMode = AppMode::HOME_SCREEN;
                
            }
            
            break;
        
        default:
            break;
        }
    }

    if (_encoder.wasClicked())
    {
        if (_appMode == AppMode::MAIN_MENU)
        {
            _menu.select();
        }
    }

    _display.render(_menu);
}   

void App::begin()
{
    _encoder.begin();
    _lcd.init();
    _lcd.backlight();

    // Add items to the menu
    _menu.addItem(&_motorItem);
    _menu.addItem(&_heaterItem);
    _menu.addItem(&_setTempItem);
    _menu.addItem(&_setSpeedItem);
    _menu.addItem(&_tuningPIDItem);
    _menu.addItem(&_exitItem);
}

void App::run()
{
    while (true)
    {
        handleUI();
    }
}


