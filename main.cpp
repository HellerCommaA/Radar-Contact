/*
 * TO DO LIST
 *
8. Event-uri random pentru emergency-uri pentru avioane si elicoptere
	-> Avioanele pot avea emergency-uri de tipul alarma cu bomba, engine fire, sanatate pacient
	-> Emergency-uri elicoptere: Engine fire (si sa isi schimbe de multe ori directia si sa
	scada rapid in altitudine)
10. De adaugat Canada, Austria, Turkey

*/

#include "./header/Menu.h"
#include "./header/Game.h"

int main() {
    srand(time(nullptr));

    try {
        ResourcesManager::Instance().load();
    } catch(ErrorLoadSound &err) {
        std::cout<<err.what();
        return 0;
    } catch(ErrorLoadFont &err) {
        std::cout<<err.what();
        return 0;
    } catch (ErrorLoadTexture &err) {
        std::cout << err.what();
        return 0;
    } catch (ErrorRegionAirports &err) {
        std::cout << err.what();
        return 0;
    } catch (ErrorRegionWeatherTiles &err) {
        std::cout << err.what();
        return 0;
    } catch (ErrorRegionLatLongBox &err) {
        std::cout << err.what();
        return 0;
    }

    {
        Menu menu;

        menu.run();
    }

    Game game;
    game.run();

    return 0;
}
