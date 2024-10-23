#ifndef CPP3_BRICKGAME_V2_0_1_SRC_GUI_CLI_CLI_INPUT_H_
#define CPP3_BRICKGAME_V2_0_1_SRC_GUI_CLI_CLI_INPUT_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Структура, содержащая все использующиеся в игре клавиши
 */
typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
} UserAction_t;

#ifdef __cplusplus
}
#endif

#endif  // CPP3_BRICKGAME_V2_0_1_SRC_GUI_CLI_CLI_INPUT_H_