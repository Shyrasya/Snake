#include "snake_model.h"

using namespace s21;

GameInfo_t::GameInfo_t()
    : score(0),
      highScore(0),
      level(1),
      speed(1),
      pause(0),
      showStartScreen(1),
      showGameOverScreen(0),
      showWinScreen(0) {
  statistInit();
}

GameInfo_t::GameInfo_t(const GameInfo_t& other) {
  allocateField();
  allocateNext();
  for (int r = 0; r < MAP_ROWS; ++r)
    for (int c = 0; c < MAP_COLS; ++c) field[r][c] = other.field[r][c];
  for (int r = 0; r < QUADR; ++r)
    for (int c = 0; c < QUADR; ++c) next[r][c] = other.next[r][c];
  score = other.score;
  highScore = other.highScore;
  level = other.level;
  speed = other.speed;
  pause = other.pause;
  showStartScreen = other.showStartScreen;
  showGameOverScreen = other.showGameOverScreen;
  showWinScreen = other.showWinScreen;
}

GameInfo_t::GameInfo_t(GameInfo_t&& other) noexcept
    : field(other.field),
      next(other.next),
      score(other.score),
      highScore(other.highScore),
      level(other.level),
      speed(other.speed),
      pause(other.pause),
      showStartScreen(other.showStartScreen),
      showGameOverScreen(other.showGameOverScreen),
      showWinScreen(other.showWinScreen) {
  other.field = nullptr;
  other.next = nullptr;
}

GameInfo_t::~GameInfo_t() {
  deallocateField();
  deallocateNext();
}

GameInfo_t& GameInfo_t::operator=(const GameInfo_t& other) {
  if (this != &other) {
    for (int r = 0; r < MAP_ROWS; r++) {
      for (int c = 0; c < MAP_COLS; c++) {
        field[r][c] = other.field[r][c];
      }
    }
    for (int r = 0; r < QUADR; r++) {
      for (int c = 0; c < QUADR; c++) {
        next[r][c] = other.next[r][c];
      }
    }
    score = other.score;
    highScore = other.highScore;
    level = other.level;
    speed = other.speed;
    pause = other.pause;
    showStartScreen = other.showStartScreen;
    showGameOverScreen = other.showGameOverScreen;
    showWinScreen = other.showWinScreen;
  }
  return *this;
}

GameInfo_t& GameInfo_t::operator=(GameInfo_t&& other) {
  if (this != &other) {
    this->~GameInfo_t();
    field = other.field;
    next = other.next;
    other.field = nullptr;
    other.next = nullptr;
    score = other.score;
    highScore = other.highScore;
    level = other.level;
    speed = other.speed;
    pause = other.pause;
    showStartScreen = other.showStartScreen;
    showGameOverScreen = other.showGameOverScreen;
    showWinScreen = other.showWinScreen;
  }
  return *this;
}

int& GameInfo_t::operator()(int row, int col) { return field[row][col]; }

void GameInfo_t::statistInit() {
  allocateField();
  allocateNext();
  cleanField();
  cleanNext();
}

void GameInfo_t::allocateField() {
  field = new int*[MAP_ROWS];
  for (int r = 0; r < MAP_ROWS; ++r) field[r] = new int[MAP_COLS];
}

void GameInfo_t::allocateNext() {
  next = new int*[QUADR];
  for (int r = 0; r < QUADR; ++r) next[r] = new int[QUADR];
}

void GameInfo_t::deallocateField() {
  if (field) {
    for (int r = 0; r < MAP_ROWS; ++r) delete[] field[r];
    delete[] field;
  }
}

void GameInfo_t::deallocateNext() {
  if (next) {
    for (int r = 0; r < QUADR; ++r) delete[] next[r];
    delete[] next;
  }
}

void GameInfo_t::cleanField() {
  for (int r = 0; r < MAP_ROWS; ++r) {
    for (int c = 0; c < MAP_COLS; ++c) field[r][c] = 0;
  }
}

void GameInfo_t::cleanNext() {
  for (int r = 0; r < QUADR; ++r) {
    for (int c = 0; c < QUADR; ++c) next[r][c] = 0;
  }
}

void GameInfo_t::readHighScore() {
  std::ifstream file("high_score_snake.txt");
  if (file.is_open()) {
    if (!(file >> highScore)) highScore = 0;
  } else {
    std::ofstream ofile("high_score_snake.txt");
    if (!ofile.is_open())
      throw std::runtime_error("High score file open error");
    ofile << '0';
  }
}

void GameInfo_t::writeHighScore() {
  std::ofstream ofile("high_score_snake.txt");
  if (!ofile.is_open()) throw std::runtime_error("High score file open error");
  if (!(ofile << highScore))
    throw std::runtime_error("High score file write error");
}

void GameInfo_t::restartInfo() {
  cleanField();
  cleanNext();
  score = 0;
  highScore = 0;
  readHighScore();
  level = 1;
  speed = 1;
  pause = 0;
  showStartScreen = 0;
  showGameOverScreen = 0;
  showWinScreen = 0;
}

SnakeModel::Snake::Snake() : size_(QUADR), direct_(RIGHT) { startBodySnake(); }

void SnakeModel::Snake::startBodySnake() {
  body_.push_back(std::make_pair(MAP_ROWS - 1, MAP_COLS / 2 + 1));
  body_.push_back(std::make_pair(MAP_ROWS - 1, MAP_COLS / 2));
  body_.push_back(std::make_pair(MAP_ROWS - 1, MAP_COLS / 2 - 1));
  body_.push_back(std::make_pair(MAP_ROWS - 1, MAP_COLS / 2 - 2));
}

SnakeModel::Snake::Snake(const Snake& other)
    : body_(other.body_), size_(other.size_), direct_(other.direct_) {}

SnakeModel::Snake::Snake(Snake&& other) noexcept
    : body_(std::move(other.body_)),
      size_(other.size_),
      direct_(other.direct_) {
  other.size_ = 0;
}

SnakeModel::Snake& SnakeModel::Snake::operator=(const Snake& other) {
  if (this != &other) {
    size_ = other.size_;
    body_ = other.body_;
    direct_ = other.direct_;
  }
  return *this;
}

SnakeModel::Snake& SnakeModel::Snake::operator=(Snake&& other) noexcept {
  if (this != &other) {
    size_ = other.size_;
    body_ = std::move(other.body_);
    direct_ = other.direct_;
    other.size_ = 0;
  }
  return *this;
}

SnakeModel::Snake::~Snake() = default;

const SnakeModel::Snake::vecpair& SnakeModel::Snake::getBody() const {
  return body_;
}

void SnakeModel::Snake::setBody(const vecpair& other) { body_ = other; }

const SnakeModel::Snake::pair& SnakeModel::Snake::getHead() const {
  return body_.front();
}

const SnakeDirection& SnakeModel::Snake::getDirect() const { return direct_; }

void SnakeModel::Snake::setDirect(SnakeDirection direct) { direct_ = direct; }

const size_t& SnakeModel::Snake::getSize() const { return size_; }

void SnakeModel::Snake::plusSize() {
  size_++;
  body_.push_back(std::make_pair(0, 0));
}

void SnakeModel::Snake::setSize(size_t value) {
  size_ = value;
  body_.resize(value);
}

bool SnakeModel::Snake::upSnake() {
  bool code = false;
  int newHeadY = getHead().first - 1;
  if (newHeadY >= QUADR) {
    int newHeadX = getHead().second;
    if (checkBodyCollision(newHeadY, newHeadX)) {
      body_.pop_back();
      body_.insert(body_.begin(), std::make_pair(newHeadY, newHeadX));
      code = true;
    }
  }
  return code;
}

bool SnakeModel::Snake::downSnake() {
  bool code = false;
  int newHeadY = Snake::getHead().first + 1;
  if (newHeadY < MAP_ROWS) {
    int newHeadX = getHead().second;
    if (checkBodyCollision(newHeadY, newHeadX)) {
      body_.pop_back();
      body_.insert(body_.begin(), std::make_pair(newHeadY, newHeadX));
      code = true;
    }
  }
  return code;
}

bool SnakeModel::Snake::leftSnake() {
  bool code = false;
  int newHeadX = Snake::getHead().second - 1;
  if (newHeadX >= 0) {
    int newHeadY = getHead().first;
    if (checkBodyCollision(newHeadY, newHeadX)) {
      body_.pop_back();
      body_.insert(body_.begin(), std::make_pair(newHeadY, newHeadX));
      code = true;
    }
  }
  return code;
}

bool SnakeModel::Snake::rightSnake() {
  bool code = false;
  int newHeadX = Snake::getHead().second + 1;
  if (newHeadX < MAP_COLS) {
    int newHeadY = getHead().first;
    if (checkBodyCollision(newHeadY, newHeadX)) {
      body_.pop_back();
      body_.insert(body_.begin(), std::make_pair(newHeadY, newHeadX));
      code = true;
    }
  }
  return code;
}

bool SnakeModel::Snake::checkBodyCollision(int newHeadY, int newHeadX) {
  bool code = true;
  for (size_t i = 0; i < size_ - 1 && code; i++) {
    if (body_[i].first == newHeadY && body_[i].second == newHeadX) code = false;
  }
  return code;
}

bool SnakeModel::Snake::straightSnake() {
  bool code = true;
  if (getDirect() == UP) {
    if (!upSnake()) code = false;
  } else if (getDirect() == DOWN) {
    if (!downSnake()) code = false;
  } else if (getDirect() == LEFT) {
    if (!leftSnake()) code = false;
  } else if (getDirect() == RIGHT)
    if (!rightSnake()) code = false;
  return code;
}

void SnakeModel::Snake::restartSnake() {
  body_.clear();
  size_ = QUADR;
  startBodySnake();
  setDirect(RIGHT);
}

void SnakeModel::Snake::addNodeSnake(const SnakeModel::Snake::pair& pair) {
  body_.insert(body_.begin(), pair);
  size_++;
}

void SnakeModel::Snake::setBodyNode(int index, int row, int col) {
  if (index >= 0 && static_cast<size_t>(index) < size_ && row >= 0 &&
      row < MAP_ROWS && col >= 0 && col < MAP_COLS)
    body_[index] = std::make_pair(row, col);
  else
    throw std::out_of_range("Invalid index for snake body node.");
}

SnakeModel::Apple::Apple() : position_(std::make_pair(0, 0)) {}

SnakeModel::Apple::Apple(const Apple& other) : position_(other.position_) {}

SnakeModel::Apple::Apple(Apple&& other) noexcept
    : position_(std::move(other.position_)) {}

SnakeModel::Apple& SnakeModel::Apple::operator=(const Apple& other) {
  if (this != &other) position_ = other.position_;
  return *this;
}

SnakeModel::Apple& SnakeModel::Apple::operator=(Apple&& other) noexcept {
  if (this != &other) position_ = std::move(other.position_);
  return *this;
}

SnakeModel::Apple::~Apple() = default;

void SnakeModel::Apple::appleGen(const SnakeModel::Snake& snake) {
  bool valid = false;
  SnakeModel::Apple::pair newPos;
  while (!valid) {
    newPos.first = std::rand() % (MAP_ROWS - QUADR) + QUADR;
    newPos.second = std::rand() % MAP_COLS;
    const auto& snakeBody = snake.getBody();
    auto it = std::find(snakeBody.begin(), snakeBody.end(), newPos);
    if (it == snakeBody.end()) valid = true;
  }
  position_ = newPos;
}

const SnakeModel::Apple::pair& SnakeModel::Apple::getPos() const {
  return position_;
}

void SnakeModel::Apple::nulPos() { position_ = std::make_pair(0, 0); }

void SnakeModel::Apple::setPos(int row, int col) {
  if (row >= 0 && row < MAP_ROWS && col >= 0 && col < MAP_COLS)
    position_.first = row;
  position_.second = col;
}

SnakeModel::SnakeModel()
    : snake_(), apple_(), fsmState_(SnakeFsmState_t::START), gameInfo_() {
  std::srand(std::time(nullptr));
}

SnakeModel::SnakeModel(const SnakeModel& other)
    : snake_(other.snake_),
      apple_(other.apple_),
      fsmState_(other.fsmState_),
      gameInfo_(other.gameInfo_) {
  for (int r = 0; r < MAP_ROWS; ++r)
    for (int c = 0; c < MAP_COLS; ++c)
      gameInfo_.field[r][c] = other.gameInfo_.field[r][c];
  for (int r = 0; r < QUADR; ++r)
    for (int c = 0; c < QUADR; ++c)
      gameInfo_.next[r][c] = other.gameInfo_.next[r][c];
  snake_.setBody(other.snake_.getBody());
  snake_.setSize(other.snake_.getSize());
  snake_.setDirect(other.snake_.getDirect());
}

SnakeModel::SnakeModel(SnakeModel&& other) noexcept
    : snake_(std::move(other.snake_)),
      apple_(std::move(other.apple_)),
      fsmState_(std::move(other.fsmState_)),
      gameInfo_(std::move(other.gameInfo_)) {
  other.gameInfo_.field = nullptr;
  other.gameInfo_.next = nullptr;
}

SnakeModel& SnakeModel::operator=(const SnakeModel& other) {
  if (this != &other) {
    gameInfo_.deallocateField();
    gameInfo_.deallocateNext();
    apple_ = other.apple_;
    fsmState_ = other.fsmState_;
    snake_ = other.snake_;
    gameInfo_.score = other.gameInfo_.score;
    gameInfo_.highScore = other.gameInfo_.highScore;
    gameInfo_.level = other.gameInfo_.level;
    gameInfo_.speed = other.gameInfo_.speed;
    gameInfo_.pause = other.gameInfo_.pause;
    gameInfo_.showStartScreen = other.gameInfo_.showStartScreen;
    gameInfo_.showGameOverScreen = other.gameInfo_.showGameOverScreen;
    gameInfo_.showWinScreen = other.gameInfo_.showWinScreen;
    gameInfo_.allocateField();
    gameInfo_.allocateNext();
    for (int r = 0; r < MAP_ROWS; ++r) {
      for (int c = 0; c < MAP_COLS; ++c)
        gameInfo_.field[r][c] = other.gameInfo_.field[r][c];
    }
    for (int r = 0; r < QUADR; ++r) {
      for (int c = 0; c < QUADR; ++c)
        gameInfo_.next[r][c] = other.gameInfo_.next[r][c];
    }
  }
  return *this;
}

SnakeModel& SnakeModel::operator=(SnakeModel&& other) noexcept {
  if (this != &other) {
    gameInfo_.deallocateField();
    gameInfo_.deallocateNext();
    apple_ = std::move(other.apple_);
    fsmState_ = std::move(other.fsmState_);
    snake_ = std::move(other.snake_);

    gameInfo_.field = other.gameInfo_.field;
    gameInfo_.next = other.gameInfo_.next;
    other.gameInfo_.field = nullptr;
    other.gameInfo_.next = nullptr;
    gameInfo_.score = other.gameInfo_.score;
    gameInfo_.highScore = other.gameInfo_.highScore;
    gameInfo_.level = other.gameInfo_.level;
    gameInfo_.speed = other.gameInfo_.speed;
    gameInfo_.pause = other.gameInfo_.pause;
    gameInfo_.showStartScreen = other.gameInfo_.showStartScreen;
    gameInfo_.showGameOverScreen = other.gameInfo_.showGameOverScreen;
    gameInfo_.showWinScreen = other.gameInfo_.showWinScreen;
    other.gameInfo_.score = 0;
    other.gameInfo_.highScore = 0;
    other.gameInfo_.level = 0;
    other.gameInfo_.speed = 0;
    other.gameInfo_.pause = 0;
    other.gameInfo_.showStartScreen = 0;
    other.gameInfo_.showGameOverScreen = 0;
    other.gameInfo_.showWinScreen = 0;
  }
  return *this;
}

SnakeModel::~SnakeModel() = default;

s21::GameInfo_t& SnakeModel::getGameInfo() { return gameInfo_; }

const SnakeFsmState_t& SnakeModel::getState() const { return fsmState_; }

SnakeModel::Snake& SnakeModel::getSnake() { return snake_; }

SnakeModel::Apple& SnakeModel::getApple() { return apple_; }

void SnakeModel::setState(SnakeFsmState_t state) { fsmState_ = state; }

void SnakeModel::fsmSpawn() {
  gameInfo_.showWinScreen = 0;
  gameInfo_.showGameOverScreen = 0;
  gameInfo_.showStartScreen = 0;
  apple_.appleGen(snake_);
  snakeAppleToGameInfo();
}

void SnakeModel::setPause() { gameInfo_.pause = 1; }

void SnakeModel::setNoPause() { gameInfo_.pause = 0; }

bool SnakeModel::validInput(SnakeDirection inputAction) {
  SnakeDirection dir = getSnake().getDirect();
  return (dir != inputAction && dir != contrAction(inputAction));
}

SnakeDirection SnakeModel::contrAction(SnakeDirection inputAction) {
  SnakeDirection contr = DOWN;
  if (inputAction == UP)
    contr = DOWN;
  else if (inputAction == DOWN)
    contr = UP;
  else if (inputAction == LEFT)
    contr = RIGHT;
  else if (inputAction == RIGHT)
    contr = LEFT;
  return contr;
}

int SnakeModel::fsmShifting(SnakeDirection shiftAction) {
  using SS = ShiftState;
  int code = SS::PLUS;
  if (!appleCheck(shiftAction)) {
    if (shiftSnake(shiftAction))
      code = SS::MOVE;
    else
      code = SS::GMOVR;
  } else {
    if (shiftAction != STRAIGHT) getSnake().setDirect(shiftAction);
  }
  return code;
}

bool SnakeModel::shiftSnake(SnakeDirection shiftAction) {
  bool code = false;
  clearSnakeAppleField();
  if (shiftAction == UP) {
    if (getSnake().upSnake()) code = true;
  } else if (shiftAction == DOWN) {
    if (getSnake().downSnake()) code = true;
  } else if (shiftAction == LEFT) {
    if (getSnake().leftSnake()) code = true;
  } else if (shiftAction == RIGHT) {
    if (getSnake().rightSnake()) code = true;
  } else if (shiftAction == STRAIGHT)
    if (getSnake().straightSnake()) code = true;
  if (code) {
    snakeAppleToGameInfo();
    if (shiftAction != STRAIGHT) getSnake().setDirect(shiftAction);
  }
  return code;
}

bool SnakeModel::appleCheck(SnakeDirection shiftAction) {
  int firstSnake = getSnake().getHead().first;
  int secondSnake = getSnake().getHead().second;
  const auto& applePos = getApple().getPos();
  if (shiftAction == STRAIGHT) shiftAction = getSnake().getDirect();
  if (shiftAction == UP)
    firstSnake--;
  else if (shiftAction == LEFT)
    secondSnake--;
  else if (shiftAction == DOWN)
    firstSnake++;
  else if (shiftAction == RIGHT)
    secondSnake++;
  return (firstSnake == applePos.first && secondSnake == applePos.second);
}

bool SnakeModel::fsmAdd() {
  getSnake().addNodeSnake(getApple().getPos());
  getApple().nulPos();
  snakeAppleToGameInfo();
  int curScore = ++getGameInfo().score;
  if (curScore > getGameInfo().highScore) getGameInfo().highScore = curScore;
  if (curScore % 5 == 0 && getGameInfo().level < 10) {
    getGameInfo().level++;
    getGameInfo().speed++;
  }
  return (gameInfo_.score < 196);
}

void SnakeModel::fsmWin() {
  gameInfo_.showWinScreen = 1;
  gameInfo_.showStartScreen = 0;
  gameInfo_.showGameOverScreen = 0;
}

void SnakeModel::fsmGameOver() {
  gameInfo_.showGameOverScreen = 1;
  gameInfo_.showWinScreen = 0;
  gameInfo_.showStartScreen = 0;
  gameInfo_.writeHighScore();
}

void SnakeModel::restartGame() {
  snake_.restartSnake();
  apple_.nulPos();
  gameInfo_.restartInfo();
  snakeAppleToGameInfo();
}

void SnakeModel::clearSnakeAppleField() {
  const auto& snakeBody = getSnake().getBody();
  for (const auto& segment : snakeBody) {
    int row = segment.first;
    int col = segment.second;
    getGameInfo().field[row][col] = 0;
  }
  int appleY = getApple().getPos().first;
  int appleX = getApple().getPos().second;
  getGameInfo().field[appleY][appleX] = 0;
}

void SnakeModel::snakeAppleToGameInfo() {
  const auto& snakeBody = getSnake().getBody();
  for (const auto& segment : snakeBody) {
    int row = segment.first;
    int col = segment.second;
    getGameInfo().field[row][col] = 1;
  }
  int headY = snakeBody.front().first;
  int headX = snakeBody.front().second;
  getGameInfo().field[headY][headX] = 3;
  int appleY = getApple().getPos().first;
  int appleX = getApple().getPos().second;
  getGameInfo().field[appleY][appleX] = 4;
}
