
#include "debug.h"
#include "input.h"
#include "controller.h"
#include "scenes/pressstart.h"
#include "controllers/pressstart.h"

#include "utility/bool.h"

/* Criamos um código pedante de mapeamento de controle usando macros */
NEW_CONTROLLER(PressStart);

static void press_any_shift() {
    PressStart_confirm();
}

static void PressStartController_init() {
    EVENT_ASSOCIATE(press, P1_MARU, press_any_shift);
    EVENT_ASSOCIATE(press, P2_MARU, press_any_shift);
    logprint(success_msg);
}
