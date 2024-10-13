/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** CoreModule
*/

#include <CoreModule.hpp>
// #include <Error.hpp>

/**
 * @brief Construct a new rtype::Core Module::Core Module object
 *
 */
rtype::CoreModule::CoreModule() {
  this->_componentManager = std::make_shared<component::ComponentManager>();
  this->_systemManager = std::make_shared<ECS_system::SystemManager>();
  this->_entityManager = std::make_shared<entity::EntityManager>();
  //   this->_coreStatus = CoreStatus::SELECTION;
  //   this->_gameModule = nullptr;
  //   this->_graphicModule = nullptr;
  //   // MenuData
  //   this->_menuData._username = "";
  //   this->_menuData.indexGame = 0;
  //   this->_menuData.indexGraphic = 0;
  //   this->_menuData._description = "\nLegend:\nPress UP/DOWN to navigate\n\
// Press ENTER to confirm the choice\n\
// Press TAB to switch to the next section";
  //   this->_menuData._type = rtype::ICoreModule::MenuSelection::USERNAME;
  //   this->_timers.push_back({std::chrono::steady_clock::now(),
  //                            std::chrono::steady_clock::now(),
  //                            std::chrono::milliseconds(0)});
  //   srand(time(NULL));
}

/**
 * @brief Destroy the rtype::Core Module::Core Module object
 *
 */
rtype::CoreModule::~CoreModule() {
  // if (this->_libList.size() > 0) {
  //   for (auto &loader : rtype::CoreModule::_libList) {
  //     loader.DLLunloader();
  //   }
  // }
  // if (this->_nameLoader.size() > 0) {
  //   for (auto &loader : rtype::CoreModule::_nameLoader) {
  //     loader.DLLunloader();
  //   }
  // }
  // if (this->_interfaceList.size() > 0) {
  //   for (auto &loader : rtype::CoreModule::_interfaceList) {
  //     loader.first.DLLunloader();
  //     loader.second.DLLunloader();
  //   }
  // }
}

// /**
//  * @brief get the status of the core module
//  *
//  * @return CoreStatus
//  */
// void rtype::CoreModule::setCoreStatus(CoreStatus status)
// {
//   this->_coreStatus = status;
// }

// /**
//  * @brief get the status of the core module
//  *
//  * @return CoreStatus
//  */
// rtype::CoreModule::CoreStatus rtype::CoreModule::getCoreStatus() const
// {
//   return this->_coreStatus;
// }

// /**
//  * @brief get the display module
//  *
//  * @return rtype::IDisplayModule *
//  */
// rtype::IDisplayModule *rtype::CoreModule::getGraphicModule()
// {
//   return this->_graphicModule;
// }

// /**
//  * @brief get the game module
//  *
//  * @return rtype::IGameModule *
//  */
// rtype::IGameModule *rtype::CoreModule::getGameModule()
// {
//   return this->_gameModule;
// }

// /**
//  * @brief set graphic or game module to the core module
//  *
//  * @param module to set
//  * @param type of the module (graphic or game)
//  */

// void rtype::CoreModule::setGraphicModule(
//     std::unique_ptr<rtype::IDisplayModule> module)
// {
//   this->_graphicModule = module.release();
// }

// void rtype::CoreModule::setGameModule(
//     std::unique_ptr<rtype::IGameModule> module)
// {
//   this->_gameModule = module.release();
// }

// void rtype::CoreModule::addLibList(std::string pathLib, std::string module)
// {
//   // rtype::CoreModule::DLLoader<rtype::ModuleType> loader(pathLib);
//   rtype::CoreModule::_libList.push_back(DLLoader<rtype::ModuleType>(pathLib));
//   rtype::ModuleType module =
//       rtype::CoreModule::_libList.back().getInstance("getType");
//   // rtype::ModuleType module = loader.getInstance("getType");
//   switch (module) {
//   case rtype::ModuleType::GAME:
//     this->_menuData._gameLibList.push_back(pathLib);
//     break;
//   case rtype::ModuleType::GRAPHIC:
//     this->_menuData._graphicLibList.push_back(pathLib);
//     break;
//   default:
//     throw std::exception();
//   }
// }

// /**
//  * @brief get the list of libraries in the given path
//  *
//  * @param pathLib path to the libraries
//  */
// void rtype::CoreModule::getLib(std::string pathLib)
// {
//   std::vector<std::string> matchedFiles;
//   DIR *dir;
//   struct dirent *entry;

//   dir = opendir(pathLib.c_str());
//   if (dir == nullptr) {
//     perror("opendir");
//     try {
//       throw OpendirException("Could not open directory");
//     } catch (OpendirException &e) {
//       std::cerr << e.what() << std::endl;
//     }
//   }
//   while ((entry = readdir(dir)) != nullptr) {
//     if (strncmp(entry->d_name, "arcade_", strlen("arcade_")) == 0 &&
//         strncmp(&(entry->d_name[strlen(entry->d_name) - 3]), ".so", 3) == OK)
//         {
//       matchedFiles.push_back(std::string(entry->d_name));
//     }
//   }
//   closedir(dir);

//   for (std::string file : matchedFiles) {
//     file = pathLib + file;
//     try {
//       this->addLibList(file);
//     } catch (const std::exception &e) {
//       std::cerr << e.what() << '\n';
//       throw std::exception();
//     }
//   }
// }

// void rtype::CoreModule::loadLib(std::string pathLib)
// {
//   rtype::CoreModule::_libList.push_back(
//       rtype::CoreModule::DLLoader<rtype::ModuleType>(pathLib));
//   rtype::ModuleType module =
//       rtype::CoreModule::_libList.back().getInstance("getType");
//   rtype::CoreModule::_interfaceList.emplace_back(
//       DLLoader<std::unique_ptr<rtype::IModuleEngine>>(pathLib));
//   switch (module) {
//   case rtype::ModuleType::GAME:
//     if (this->_gameModule) {
//       delete this->_gameModule;
//     }
//     this->_gameModule =
//         std::move(rtype::CoreModule::_interfaceList.back().second.getInstance(
//                       "entryPoint"))
//             .release();
//     this->_gameModule->setCoreModule(this);
//     this->_gameModule->init();
//     break;
//   case rtype::ModuleType::GRAPHIC:
//     if (this->_graphicModule) {
//       rtype::CoreModule::_nameLoader.push_back(DLLoader<std::string>(pathLib));
//       // DLLoader<std::string> loaderTypeModule(pathLib);
//       std::string moduleName = _nameLoader.back().getInstance("getName");
//       if (moduleName == this->_graphicModule->getName())
//         return;
//       delete this->_graphicModule;
//     }
//     this->_graphicModule =
//         std::move(rtype::CoreModule::_interfaceList.back().first.getInstance(
//                       "entryPoint"))
//             .release();
//     this->_graphicModule->setCoreModule(this);
//     break;
//   default:
//     try {
//       throw BadModuleTypeException("Bad module type");
//     } catch (BadModuleTypeException &e) {
//       std::cerr << e.what() << std::endl;
//     }
//     break;
//   }
//   this->_menuData.indexGame = this->_menuData._gameLibList.size() / 2;
//   this->_menuData.indexGraphic = this->_menuData._graphicLibList.size() / 2;
// }

// void rtype::CoreModule::generateScore()
// {
//   mkdir("scoreArcade", 0777);

//   // Create a file
//   std::ofstream outputFile;

//   for (std::string game_lib_path : this->_menuData._gameLibList) {
//     rtype::CoreModule::_nameLoader.push_back(
//         DLLoader<std::string>(game_lib_path));
//     std::string moduleName = _nameLoader.back().getInstance("getName");
//     FILE *fd = fopen(("scoreArcade/" + moduleName + ".txt").c_str(), "r");
//     if (fd) {
//       fclose(fd);
//       break;
//     } else {
//       outputFile.open("scoreArcade/" + moduleName + ".txt");
//       if (!outputFile.is_open()) {
//         std::cerr << "Error creating file!" << std::endl;
//       }
//       outputFile.close();
//     }
//   }
// }

// void rtype::CoreModule::launchSelection()
// {
//   if (this->_menuData._username == "" ||
//       this->_menuData._username == "Please enter a username") {
//     this->_menuData._username = "Please enter a username";
//     this->_menuData._type = rtype::ICoreModule::MenuSelection::USERNAME;
//   } else {
//     this->loadLib(this->_menuData._gameLibList[this->_menuData.indexGame]);
//     this->loadLib(
//         this->_menuData._graphicLibList[this->_menuData.indexGraphic]);
//     this->_coreStatus = CoreStatus::RUNNING;
//   }
// }

// void rtype::CoreModule::addCharUsername(char c)
// {
//   if (this->_menuData._username == "Please enter a username")
//     this->_menuData._username = "";
//   this->_menuData._username += c;
// }

// void rtype::CoreModule::handleKeySelection(rtype::KeyboardInput key)
// {
//   switch (this->_menuData._type) {
//   case rtype::ICoreModule::MenuSelection::USERNAME:
//     switch (key) {
//     case rtype::KeyboardInput::A:
//       addCharUsername('a');
//       break;
//     case rtype::KeyboardInput::B:
//       addCharUsername('b');
//       break;
//     case rtype::KeyboardInput::C:
//       addCharUsername('c');
//       break;
//     case rtype::KeyboardInput::D:
//       addCharUsername('d');
//       break;
//     case rtype::KeyboardInput::E:
//       addCharUsername('e');
//       break;
//     case rtype::KeyboardInput::F:
//       addCharUsername('f');
//       break;
//     case rtype::KeyboardInput::G:
//       addCharUsername('g');
//       break;
//     case rtype::KeyboardInput::H:
//       addCharUsername('h');
//       break;
//     case rtype::KeyboardInput::I:
//       addCharUsername('i');
//       break;
//     case rtype::KeyboardInput::J:
//       addCharUsername('j');
//       break;
//     case rtype::KeyboardInput::K:
//       addCharUsername('k');
//       break;
//     case rtype::KeyboardInput::L:
//       addCharUsername('l');
//       break;
//     case rtype::KeyboardInput::M:
//       addCharUsername('m');
//       break;
//     case rtype::KeyboardInput::N:
//       addCharUsername('n');
//       break;
//     case rtype::KeyboardInput::O:
//       addCharUsername('o');
//       break;
//     case rtype::KeyboardInput::P:
//       addCharUsername('p');
//       break;
//     case rtype::KeyboardInput::Q:
//       addCharUsername('q');
//       break;
//     case rtype::KeyboardInput::R:
//       addCharUsername('r');
//       break;
//     case rtype::KeyboardInput::S:
//       addCharUsername('s');
//       break;
//     case rtype::KeyboardInput::T:
//       addCharUsername('t');
//       break;
//     case rtype::KeyboardInput::U:
//       addCharUsername('u');
//       break;
//     case rtype::KeyboardInput::V:
//       addCharUsername('v');
//       break;
//     case rtype::KeyboardInput::W:
//       addCharUsername('w');
//       break;
//     case rtype::KeyboardInput::X:
//       addCharUsername('x');
//       break;
//     case rtype::KeyboardInput::Y:
//       addCharUsername('y');
//       break;
//     case rtype::KeyboardInput::Z:
//       addCharUsername('z');
//       break;
//     case rtype::KeyboardInput::ENTER:
//       this->launchSelection();
//       break;
//     case rtype::KeyboardInput::BACKSPACE:
//       if (!this->_menuData._username.empty())
//         this->_menuData._username.pop_back();
//       break;
//     case rtype::KeyboardInput::TAB:
//       this->_menuData._type = rtype::ICoreModule::MenuSelection::GRAPHIC;
//       break;
//     case rtype::KeyboardInput::ESCAPE:
//       this->_coreStatus = CoreStatus::EXIT;
//       break;
//     case rtype::KeyboardInput::CROSS:
//       this->_coreStatus = CoreStatus::EXIT;
//       break;
//     }
//     break;
//   case rtype::ICoreModule::MenuSelection::GRAPHIC:
//     switch (key) {
//     case rtype::KeyboardInput::UP:
//       this->_menuData._graphicLibList.push_back(
//           this->_menuData._graphicLibList.front());
//       this->_menuData._graphicLibList.erase(
//           this->_menuData._graphicLibList.begin());
//       break;
//     case rtype::KeyboardInput::DOWN:
//       this->_menuData._graphicLibList.insert(
//           this->_menuData._graphicLibList.begin(),
//           this->_menuData._graphicLibList.back());
//       this->_menuData._graphicLibList.pop_back();
//       break;
//     case rtype::KeyboardInput::ENTER:
//       this->launchSelection();
//       break;
//     case rtype::KeyboardInput::TAB:
//       this->_menuData._type = rtype::ICoreModule::MenuSelection::GAME;
//       break;
//     case rtype::KeyboardInput::ESCAPE:
//       this->_coreStatus = CoreStatus::EXIT;
//       break;
//     case rtype::KeyboardInput::CROSS:
//       this->_coreStatus = CoreStatus::EXIT;
//       break;
//     }
//     break;
//   case rtype::ICoreModule::MenuSelection::GAME:
//     switch (key) {
//     case rtype::KeyboardInput::UP:
//       this->_menuData._gameLibList.push_back(
//           this->_menuData._gameLibList.front());
//       this->_menuData._gameLibList.erase(this->_menuData._gameLibList.begin());
//       break;
//     case rtype::KeyboardInput::DOWN:
//       this->_menuData._gameLibList.insert(this->_menuData._gameLibList.begin(),
//                                           this->_menuData._gameLibList.back());
//       this->_menuData._gameLibList.pop_back();
//       break;
//     case rtype::KeyboardInput::ENTER:
//       this->launchSelection();
//       break;
//     case rtype::KeyboardInput::TAB:
//       this->_menuData._type = rtype::ICoreModule::MenuSelection::USERNAME;
//       break;
//     case rtype::KeyboardInput::ESCAPE:
//       this->_coreStatus = CoreStatus::EXIT;
//       break;
//     case rtype::KeyboardInput::CROSS:
//       this->_coreStatus = CoreStatus::EXIT;
//       break;
//     }
//     break;
//   default:
//     std::cerr << "Bad MenuSelection" << std::endl;
//     break;
//   }
// }

// void rtype::CoreModule::handleKeyRunning(rtype::KeyboardInput key)
// {
//   switch (key) {
//   case rtype::KeyboardInput::CROSS:
//     this->_coreStatus = CoreStatus::EXIT;
//     break;
//   case rtype::KeyboardInput::Q:
//     this->_coreStatus = CoreStatus::EXIT;
//     break;
//   case rtype::KeyboardInput::D:
//     this->_menuData._graphicLibList.push_back(
//         this->_menuData._graphicLibList.front());
//     this->_menuData._graphicLibList.erase(
//         this->_menuData._graphicLibList.begin());
//     this->loadLib(
//         this->_menuData._graphicLibList[this->_menuData.indexGraphic]);
//     break;
//   case rtype::KeyboardInput::G:
//     this->_menuData._gameLibList.push_back(
//         this->_menuData._gameLibList.front());
//     this->_menuData._gameLibList.erase(this->_menuData._gameLibList.begin());
//     this->loadLib(this->_menuData._gameLibList[this->_menuData.indexGame]);
//     break;
//   case rtype::KeyboardInput::R:
//     this->loadLib(this->_menuData._gameLibList[this->_menuData.indexGame]);
//     break;
//   case rtype::KeyboardInput::ESCAPE:
//     this->_coreStatus = CoreStatus::SELECTION;
//     break;
//   }
// }

// void rtype::CoreModule::handleKeyEvent(rtype::KeyboardInput key)
// {
//   switch (this->_coreStatus) {
//   case CoreStatus::SELECTION:
//     this->handleKeySelection(key);
//     break;
//   case CoreStatus::RUNNING:
//     this->handleKeyRunning(key);
//     break;
//   default:
//     throw std::exception();
//   }
// }

// /**
//  * @brief get the menu data
//  *
//  * @return rtype::IModule::MenuData
//  */
// rtype::ICoreModule::MenuData rtype::CoreModule::getMenuData() const
// {
//   return this->_menuData;
// }

// /**
//  * @brief get the game data
//  *
//  * @return rtype::IModule::GameData
//  */
// rtype::GameData rtype::CoreModule::getGameData() const
// {
//   return this->_gameData;
// }

// /**
//  * @brief set the game data
//  *
//  * @param gameData game data to set
//  */
// void rtype::CoreModule::setGameData(rtype::GameData gameData)
// {
//   this->_gameData = gameData;
// }

// /**
//  * @brief core loop
//  *
//  * @return int
//  */
// int rtype::CoreModule::coreLoop()
// {
//   while (this->_coreStatus != CoreStatus::EXIT) {
//     switch (this->_coreStatus) {
//     case CoreStatus::SELECTION:
//       this->selectionLoop();
//       break;
//     case CoreStatus::RUNNING:
//       this->runningLoop();
//       break;
//     default:
//       throw std::exception();
//     }
//   }
//   return 0;
// }

// std::vector<std::string> split_str(std::string const &str, const char delim)
// {
//   // create a stream from the string
//   std::stringstream s(str);
//   std::vector<std::string> out;
//   std::string s2;
//   while (std::getline(s, s2, delim)) {
//     out.push_back(s2); // store the string in s2
//   }
//   return out;
// }

// static void generateFocusVersion(std::string &section, int len)
// {
//   for (int i = 0; i < len; i += 1) {
//     section = "#" + section;
//   }
//   for (int i = 1; i < section.size(); i += 1) {
//     if (section[i - 1] == '\n')
//       section[i] = '#';
//   }
//   section.pop_back();
//   for (int i = 0; i < len; i += 1) {
//     section += "#";
//   }
//   section += "\n";
// }

// int max_len_line(std::string str)
// {
//   int max = 0;
//   for (std::string line : split_str(str, '\n')) {
//     if (line.size() > max)
//       max = line.size();
//   }
//   return max;
// }

// std::vector<std::pair<std::string, int>>
// getScoreFromFile(std::string moduleName)
// {
//   std::ifstream file("scoreArcade/" + moduleName + ".txt");
//   std::string line;
//   std::vector<std::pair<std::string, int>> all_file;
//   if (file.is_open()) {
//     while (std::getline(file, line)) {
//       if (!line.empty()) {
//         std::vector<std::string> line_split = split_str(line, ':');
//         all_file.push_back(
//             std::make_pair(line_split[0], std::stoi(line_split[1])));
//       }
//     }
//     file.close();
//   }
//   // display all_file
//   for (size_t i = 0; i < all_file.size(); i += 1) {
//     for (size_t j = i + 1; j < all_file.size(); j += 1) {
//       if (all_file[i].second < all_file[j].second) {
//         std::pair<std::string, int> tmp = all_file[i];
//         all_file[i] = all_file[j];
//         all_file[j] = tmp;
//       }
//     }
//   }
//   return all_file;
// }

// /**
//  * @brief update selection
//  *
//  */
// void rtype::CoreModule::updateSelection()
// {
//   std::string selection = "";

//   // Generate the selection
//   std::string username = "\n Enter your username :\n";
//   std::string graphic = "\n selected graphic library:\n";
//   std::string game = "\n selected game library:\n";
//   std::string score = "\n Hight Score of ";

//   // Add value to the selection
//   username += " " + this->_menuData._username + " \n\n";
//   for (size_t i = 0; i < this->_menuData._graphicLibList.size(); i += 1) {
//     if (i == this->_menuData.indexGraphic)
//       graphic += " -> " + this->_menuData._graphicLibList[i] + " \n";
//     else
//       graphic += "    " + this->_menuData._graphicLibList[i] + " \n";
//   }
//   graphic += "\n";
//   for (size_t i = 0; i < this->_menuData._gameLibList.size(); i += 1) {
//     if (i == this->_menuData.indexGame)
//       game += " -> " + this->_menuData._gameLibList[i] + " \n";
//     else
//       game += "    " + this->_menuData._gameLibList[i] + " \n";
//   }
//   game += "\n";

//   // Focus version
//   int max_len = std::max(max_len_line(username),
//                          std::max(max_len_line(graphic),
//                          max_len_line(game)));
//   switch (this->_menuData._type) {
//   case rtype::ICoreModule::MenuSelection::USERNAME:
//     generateFocusVersion(username, max_len);
//     break;
//   case rtype::ICoreModule::MenuSelection::GRAPHIC:
//     generateFocusVersion(graphic, max_len);
//     break;
//   case rtype::ICoreModule::MenuSelection::GAME:
//     generateFocusVersion(game, max_len);
//     break;
//   }

//   // Add Hight score of the game
//   // DLLoader<std::string> loaderTypeModule(
//   //     this->_menuData._gameLibList[this->_menuData.indexGame]);
//   rtype::CoreModule::_nameLoader.push_back(DLLoader<std::string>(
//       this->_menuData._gameLibList[this->_menuData.indexGame]));
//   std::string moduleName = _nameLoader.back().getInstance("getName");
//   score += moduleName + " :\n";
//   std::vector<std::string> split_player_score;
//   for (size_t i = 1; i < 6; i += 1) {
//     split_player_score.push_back(std::to_string(i) + ".");
//   }
//   std::vector<std::pair<std::string, int>> all_file =
//       getScoreFromFile(moduleName);
//   // add score of player
//   for (size_t i = 0; i < all_file.size() && i < 5; i += 1) {
//     split_player_score[i] = std::to_string(i + 1) + ". " + all_file[i].first
//     +
//                             " : " + std::to_string(all_file[i].second);
//   }
//   for (std::string line : split_player_score) {
//     score += line + "\n";
//   }

//   selection = username + "\n" + graphic + "\n" + game + "\n" + score + "\n" +
//               this->_menuData._description;

//   this->getGraphicModule()->clearWindow();
//   this->getGraphicModule()->drawText(selection, 0, 0, 30);
//   this->getGraphicModule()->displayWindow();
// }

// /**
//  * @brief selection loop
//  *
//  */
// void rtype::CoreModule::selectionLoop()
// {
//   this->updateSelection();
//   while (this->_coreStatus == CoreStatus::SELECTION) {
//     rtype::KeyboardInput actualKeyPress =
//     this->getGraphicModule()->getInput();
//     this->handleKeyEvent(actualKeyPress);
//     if (actualKeyPress != rtype::KeyboardInput::NONE)
//       this->updateSelection();
//   }
// }

// void rtype::CoreModule::updateRunning()
// {
//   int game_scale = 30;
//   std::pair<char, std::string> sprite;

//   std::vector<std::vector<std::pair<int, std::vector<std::pair<int, int>>>>>
//       allLayerSpritesCoordinates;
//   std::vector<std::pair<int, std::vector<std::pair<int, int>>>>
//       allSpritesCoordinates;
//   for (int j = 0; j < this->_gameData.entities.size(); j += 1) {
//     for (auto &i : this->_gameData.sprite_value) {
//       std::vector<std::pair<int, int>> coordinates;
//       for (size_t k = 0; k < this->_gameData.entities[j].size(); k += 1) {
//         if (this->_gameData.entities[j][k].sprite == i.first)
//           coordinates.push_back(std::make_pair(
//               this->_gameData.entities[j][k].position.first,
//               this->_gameData.entities[j][k].position.second + 30));
//       }
//       allSpritesCoordinates.push_back(std::make_pair(i.first, coordinates));
//     }
//     allLayerSpritesCoordinates.push_back(allSpritesCoordinates);
//   }

//   this->getGameModule()->updateGame();
//   this->getGraphicModule()->clearWindow();
//   this->getGraphicModule()->drawText(
//       "Graphic:" + this->getGraphicModule()->getName() +
//           " | Game:" + this->getGameModule()->getName() +
//           " | Score: " + std::to_string(this->getGameData().score),
//       0,
//       0,
//       game_scale);
//   // draw sprites on map
//   for (size_t i = 0; i < this->getGameData().entities.size(); i += 1) {
//     for (size_t j = 0; j < allLayerSpritesCoordinates[i].size(); j += 1) {
//       sprite.first = allLayerSpritesCoordinates[i][j].first;
//       sprite.second = this->getGameData()
//                           .sprite_value[allLayerSpritesCoordinates[i][j].first];
//       this->getGraphicModule()->drawAllSprite(
//           sprite,
//           allLayerSpritesCoordinates[i][j].second,
//           game_scale,
//           game_scale);
//     }
//   }
//   this->getGraphicModule()->drawText(
//       this->_gameData._description,
//       0,
//       this->getGameData().entities[0].back().position.second + (2 * 30),
//       game_scale);
//   this->getGraphicModule()->displayWindow();
// }

// static void addScoreInFile(std::string path, int score, std::string username)
// {
//   std::ofstream file;
//   file.open(path, std::ios::app);
//   std::string str = username + ":" + std::to_string(score) + "\n";
//   file << str;
// }

// /**
//  * @brief running loop
//  *
//  */
// void rtype::CoreModule::runningLoop()
// {
//   rtype::KeyboardInput input;
//   this->getGraphicModule()->clearWindow();
//   while (this->_coreStatus == rtype::ICoreModule::CoreStatus::RUNNING) {
//     this->updateTimers();
//     this->updateRunning();
//     input = this->getGraphicModule()->getInput();
//     this->handleKeyEvent(input);
//     this->getGameModule()->handdleKeyEvents(input);
//   }
//   if (this->getGameModule()->getGameStatus() ==
//       rtype::IGameModule::GameStatus::WIN) {
//     this->_coreStatus = rtype::ICoreModule::SELECTION;
//     this->_gameData.score += 1000;
//     addScoreInFile("scoreArcade/" + this->getGameModule()->getName() +
//     ".txt",
//                    this->_gameData.score,
//                    this->_menuData._username);
//   } else if (this->getGameModule()->getGameStatus() ==
//              rtype::IGameModule::GameStatus::GAMEOVER) {
//     this->_coreStatus = rtype::ICoreModule::SELECTION;
//     addScoreInFile("scoreArcade/" + this->getGameModule()->getName() +
//     ".txt",
//                    this->_gameData.score,
//                    this->_menuData._username);
//   }
// }

// /**
//  * @brief update the timer
//  *
//  */
// void rtype::CoreModule::updateTimers()
// {
//   for (int i = 0; i < this->_timers.size(); i += 1) {
//     this->_timers[i].end = std::chrono::steady_clock::now();
//     this->_timers[i].duration =
//         std::chrono::duration_cast<std::chrono::milliseconds>(
//             this->_timers[i].end - this->_timers[i].start);
//   }
// }

// /**
//  * @brief reset the timer
//  *
//  */
// void rtype::CoreModule::resetTimers(int index)
// {
//   if (index >= this->_timers.size())
//     throw std::exception();
//   this->_timers[index].start = std::chrono::steady_clock::now();
// }

// /**
//  * @brief get the timer
//  *
//  * @return rtype::AGameModule::timer
//  */
// std::vector<rtype::timer> rtype::CoreModule::getTimers() const
// {
//   return this->_timers;
// }

// /**
//  * @brief get the timer
//  *
//  * @return rtype::AGameModule::timer
//  */
// void rtype::CoreModule::setTimers(std::vector<rtype::timer> timers)
// {
//   this->_timers = timers;
// }

/**
 * @brief Loads the entity constructor by dynamically loading the shared object
 * file.
 *
 * This function uses dlopen to load the entity shared object file and stores
 * the resulting entity constructor in the entityConstructor member variable.
 */
// void rtype::CoreModule::loadEntityConstructor()
// {
//   // dlopen the entity .so file
//   this->entityConstructor = std::make_shared<DLLoader<entity::IEntity>>(
//       "lib/shared_entity/r-type_shared_entity.so");
// }

// void rtype::CoreModule::loadManagers()
// {
//   // load system manager .so
//   DLLoader<ECS_system::SystemManager> systemManagerLoader(
//       "lib/shared_managers/r-type_system_manager.so");

//   // load entity manager .so
//   DLLoader<entity::EntityManager> entityManagerLoader(
//       "lib/shared_managers/r-type_entity_manager.so");

//   // load component manager .so
//   DLLoader<component::ComponentManager> componentManagerLoader(
//       "lib/shared_managers/r-type_component_manager.so");

//   this->_systemManager =
//   systemManagerLoader.getInstance("createSystemManager");
//   this->_entityManager =
//   entityManagerLoader.getInstance("createEntityManager");
//   this->_componentManager =
//       componentManagerLoader.getInstance("createComponentManager");
// }

// void rtype::CoreModule::loadSystems()
// {
//   // load audio system .so
//   DLLoader<ECS_system::ISystem> audioSystemLoader(
//       "lib/client_systems/r-type_audio_system.so");

//   // load render system .so
//   DLLoader<ECS_system::ISystem> renderSystemLoader(
//       "lib/client_systems/r-type_render_system.so");

//   this->_systems.push_back(audioSystemLoader.getInstance(
//       "createAudioSystem", this->_componentManager));
//   this->_systems.push_back(renderSystemLoader.getInstance(
//       "createRenderSystem", this->_componentManager));
// }

// void rtype::CoreModule::loadComponents()
// {
//   // load music component .so
//   this->_components.emplace(
//       "music", std::make_shared<DLLoader<component::IComponent>>(
//                    "lib/client_components/r-type_music_component.so"));

//   // load sound component .so
//   this->_components.emplace(
//       "sound", std::make_shared<DLLoader<component::IComponent>>(
//                    "lib/client_components/r-type_sound_component.so"));

//   // load sprite component .so
//   this->_components.emplace(
//       "sprite", std::make_shared<DLLoader<component::IComponent>>(
//                     "lib/client_components/r-type_sprite_component.so"));

//   // load texture component .so
//   this->_components.emplace(
//       "texture", std::make_shared<DLLoader<component::IComponent>>(
//                      "lib/client_components/r-type_texture_component.so"));

//   // load position component .so
//   this->_components.emplace(
//       "position", std::make_shared<DLLoader<component::IComponent>>(
//                       "lib/shared_components/r-type_position_component.so"));
// }

// std::vector<std::shared_ptr<ECS_system::ISystem>>
// rtype::CoreModule::getSystems() const
// {
//   return this->_systems;
// }

std::shared_ptr<entity::EntityManager>
rtype::CoreModule::getEntityManager() const {
  return this->_entityManager;
}

std::shared_ptr<component::ComponentManager>
rtype::CoreModule::getComponentManager() const {
  return this->_componentManager;
}

std::shared_ptr<ECS_system::SystemManager>
rtype::CoreModule::getSystemManager() const {
  return this->_systemManager;
}

void rtype::CoreModule::run() {
  sf::Clock clock;
  while (1) {
    float deltatime = clock.restart().asSeconds();
    this->getSystemManager()->update(deltatime,
                                     this->getEntityManager()->getEntities());
  }
}

entity::IEntity *rtype::CoreModule::createBackground(uint32_t entityID, std::string texturePath, sf::Vector2f speed, sf::Vector2f size)
{
  auto background = this->getEntityManager()->createEntity(entityID);

  this->getComponentManager()->addComponent<component::PositionComponent>(
      entityID, 0.0f, 0.0f);
  this->getComponentManager()->addComponent<component::ScrollComponent>(
      entityID, speed);
  this->getComponentManager()
      ->addComponent<component::BackgroundComponent>(
          entityID, texturePath, size);

  return background;
}

entity::IEntity *rtype::CoreModule::createPlayer(uint32_t entityID, std::string texturePath, sf::Vector2f position, sf::Vector2f velocity, sf::Vector2f scale)
{
  auto player = this->getEntityManager()->createEntity(entityID);

  this->getComponentManager()->addComponent<component::PositionComponent>(
      entityID, position.x, position.y);
  this->getComponentManager()->addComponent<component::SpriteComponent>(
      entityID, position.x, position.y);
  this->getComponentManager()->addComponent<component::TextureComponent>(
      entityID, texturePath);
  this->getComponentManager()->addComponent<component::InputComponent>(entityID);
  this->getComponentManager()->addComponent<component::VelocityComponent>(
      entityID, velocity);
  this->getComponentManager()
      ->addComponent<component::TransformComponent>(
          entityID, position, scale);

  return player;
}

void rtype::CoreModule::init()
{
  this->createPlayer(0, "app/assets/sprites/r-typesheet1.gif", sf::Vector2f(100.0f, 100.0f), sf::Vector2f(10.0f, 0.0f), sf::Vector2f(1.0f, 1.0f));
  this->createBackground(1, "app/assets/images/city_background.png", sf::Vector2f(100.0f, 0.0f), sf::Vector2f(1920.0f, 1080.0f));

  component::ComponentManager &componentManager =
      *this->getComponentManager();

  this->getSystemManager()->addSystem(componentManager, "AudioSystem");
  this->getSystemManager()->addSystem(componentManager, "RenderSystem");
  this->getSystemManager()->addSystem(componentManager, "InputSystem");
  this->getSystemManager()->addSystem(componentManager, "MovementSystem");
  this->getSystemManager()->addSystem(componentManager,
                                      "BackgroundSystem");

  this->getComponentManager()
      ->getComponent<component::InputComponent>(0)
      ->bindAction("MoveLeft", sf::Keyboard::A);
  this->getComponentManager()
      ->getComponent<component::InputComponent>(0)
      ->bindAction("MoveRight", sf::Keyboard::D);
  this->getComponentManager()
      ->getComponent<component::InputComponent>(0)
      ->bindAction("MoveUp", sf::Keyboard::W);
  this->getComponentManager()
      ->getComponent<component::InputComponent>(0)
      ->bindAction("MoveDown", sf::Keyboard::S);
}