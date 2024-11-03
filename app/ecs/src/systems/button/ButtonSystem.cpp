/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** ButtonComponent
*/

#include <systems/ButtonSystem.hpp>

namespace ECS_system
{
    /**
     * @brief Construct a new Button System object
     * 
     * @param componentManager Reference to the ComponentManager
     * @param entityManager Reference to the EntityManager
     * @param graphic Shared pointer to the IGraphic interface
     * @param audio Shared pointer to the IAudio interface
     * @param stringCom StringCom object
     */
    ButtonSystem::ButtonSystem(
        component::ComponentManager &componentManager,
        entity::EntityManager &entityManager,
        std::shared_ptr<IGraphic> graphic, std::shared_ptr<IAudio> audio, StringCom stringCom)
        : ASystem(componentManager, entityManager, graphic, audio, stringCom)
    {
    }

    /**
     * @brief Binds a keyboard key to a specific action and updates the key bindings configuration file.
     *
     * This function reads the current key bindings from a JSON configuration file, updates the binding
     * for the specified action with the provided key, and writes the updated bindings back to the file.
     *
     * @param key The keyboard key to bind to the action.
     * @param action The action to bind the key to.
     *
     * @throws std::runtime_error If the configuration file cannot be opened for writing.
     */
    void ButtonSystem::bindTheKey(KeyBoard key, Action action)
    {
        std::ifstream file("configs/keyBind.json");
        nlohmann::json json;

        if (file.is_open())
            file >> json;

        try
        {
            json[std::to_string(static_cast<int>(action))] = static_cast<int>(key);
            std::ofstream file2("configs/keyBind.json");
            if (!file2.is_open())
                throw std::runtime_error("Failed to open file: configs/keyBind.json");
            file2 << json.dump(4);
            file.close();
            file2.close();
        }
        catch (std::exception &e)
        {
            std::cerr << e.what() << std::endl;
            file.close();
        }
    }

    /**
     * @brief Changes the text of a TextComponent based on the provided keyboard key.
     * 
     * This function retrieves the TextComponent associated with the given ID and updates its text
     * based on the specified keyboard key. If the TextComponent is not found, the function returns
     * without making any changes.
     * 
     * @param id The ID of the entity whose TextComponent is to be updated.
     * @param key The keyboard key that determines the new text for the TextComponent.
     * @param graphic A shared pointer to the IGraphic interface used for rendering the text.
     */
    void ButtonSystem::changeText(size_t id, KeyBoard key, std::shared_ptr<IGraphic> graphic)
    {
        component::TextComponent *text = _componentManager.getComponent<component::TextComponent>(id);
        if (!text)
            return;
        switch (key)
        {
        case KeyBoard::A:
            text->setText("A", graphic);
            break;
        case KeyBoard::B:
            text->setText("B", graphic);
            break;
        case KeyBoard::C:
            text->setText("C", graphic);
            break;
        case KeyBoard::D:
            text->setText("D", graphic);
            break;
        case KeyBoard::E:
            text->setText("E", graphic);
            break;
        case KeyBoard::F:
            text->setText("F", graphic);
            break;
        case KeyBoard::G:
            text->setText("G", graphic);
            break;
        case KeyBoard::H:
            text->setText("H", graphic);
            break;
        case KeyBoard::I:
            text->setText("I", graphic);
            break;
        case KeyBoard::J:
            text->setText("J", graphic);
            break;
        case KeyBoard::K:
            text->setText("K", graphic);
            break;
        case KeyBoard::L:
            text->setText("L", graphic);
            break;
        case KeyBoard::M:
            text->setText("M", graphic);
            break;
        case KeyBoard::N:
            text->setText("N", graphic);
            break;
        case KeyBoard::O:
            text->setText("O", graphic);
            break;
        case KeyBoard::P:
            text->setText("P", graphic);
            break;
        case KeyBoard::Q:
            text->setText("Q", graphic);
            break;
        case KeyBoard::R:
            text->setText("R", graphic);
            break;
        case KeyBoard::S:
            text->setText("S", graphic);
            break;
        case KeyBoard::T:
            text->setText("T", graphic);
            break;
        case KeyBoard::U:
            text->setText("U", graphic);
            break;
        case KeyBoard::V:
            text->setText("V", graphic);
            break;
        case KeyBoard::W:
            text->setText("W", graphic);
            break;
        case KeyBoard::X:
            text->setText("X", graphic);
            break;
        case KeyBoard::Y:
            text->setText("Y", graphic);
            break;
        case KeyBoard::Z:
            text->setText("Z", graphic);
            break;
        case KeyBoard::escape:
            text->setText("Escape", graphic);
            break;
        case KeyBoard::Space:
            text->setText("Space", graphic);
            break;
        default:
            break;
        }
    }

    /**
     * @brief Changes the input binding for entities with InputComponent and TypeComponent.
     *
     * This function iterates through the provided entities and updates the input binding
     * for those that have both InputComponent and TypeComponent. If the entity's type is
     * PLAYER, it binds the specified action to the given key.
     *
     * @param entities A vector of shared pointers to IEntity objects to be processed.
     * @param key The keyboard key to bind the action to.
     * @param action The action to be bound to the specified key.
     */
    void ButtonSystem::changeInput(std::vector<std::shared_ptr<entity::IEntity>> entities, KeyBoard key, Action action)
    {
        for (auto &entity : _componentManager.getEntitiesWithComponents<component::InputComponent, component::TypeComponent>(entities))
        {
            component::InputComponent *input = _componentManager.getComponent<component::InputComponent>(entity->getID());
            component::TypeComponent *type = _componentManager.getComponent<component::TypeComponent>(entity->getID());
            if (type->getType() == Type::PLAYER)
                input->bindAction(action, key);
        }
    }

    /**
     * @brief Retrieves the key binding for a given action from a JSON configuration file.
     *
     * This function reads the key bindings from the "configs/keyBind.json" file and returns the key
     * associated with the specified action. If the action is not found in the JSON file, the provided
     * default key is returned.
     *
     * @param action The action for which the key binding is to be retrieved.
     * @param key The default key to be returned if the action is not found in the JSON file.
     * @return The key binding for the specified action, or the default key if the action is not found.
     * @throws std::runtime_error If the JSON configuration file cannot be opened.
     */
    static KeyBoard getKey(Action action, KeyBoard key)
    {
        std::ifstream file("configs/keyBind.json");

        if (!file.is_open())
            throw std::runtime_error("Failed to open file: configs/keyBind.json");

        nlohmann::json json;

        file >> json;
        file.close();
        // check if the key is already binded
        try
        {
            int actionJson = static_cast<int>(action);
            if (json.contains(std::to_string(actionJson)))
            {
                int keyBind = json[std::to_string(actionJson)];
                return static_cast<KeyBoard>(keyBind);
            }
            else
                return key;
        }
        catch (std::exception &e)
        {
            return key;
        }
    }

    /**
     * @brief Updates the button system.
     * 
     * This function processes all entities with OnClickComponent, RectangleShapeComponent, 
     * TransformComponent, and TypeComponent. It checks for mouse interactions and updates 
     * the state of buttons accordingly.
     * 
     * @param deltaTime The time elapsed since the last update.
     * @param entities A vector of shared pointers to entities to be processed.
     * @param msgToSend A reference to a vector of pairs where each pair contains an action 
     *        and an entity ID to be sent as a message.
     * @param msgReceived A reference to a vector of pairs where each pair contains a string 
     *        and a pair of size_t values representing received messages.
     * @param entityMutex A mutex to ensure thread-safe access to entities.
     * @param sceneStatus A shared pointer to the current scene status.
     */
    void ButtonSystem::update(float deltaTime, std::vector<std::shared_ptr<entity::IEntity>> entities, std::vector<std::pair<Action, size_t>> &msgToSend, std::vector<std::pair<std::string, std::pair<size_t, size_t>>> &msgReceived, std::mutex &entityMutex, std::shared_ptr<Scene> &sceneStatus)
    {
        std::lock_guard<std::mutex> lock(entityMutex);
        for (auto &entity : _componentManager.getEntitiesWithComponents<component::OnClickComponent,
                                                                        component::RectangleShapeComponent, component::TransformComponent, component::TypeComponent>(entities))
        {
            if (entity->getSceneStatus() != *sceneStatus && entity->getSceneStatus() != Scene::ALL)
                continue;
            component::TypeComponent *type = _componentManager.getComponent<component::TypeComponent>(entity->getID());
            component::OnClickComponent *onClick = _componentManager.getComponent<component::OnClickComponent>(entity->getID());
            component::RectangleShapeComponent *rectangle = _componentManager.getComponent<component::RectangleShapeComponent>(entity->getID());
            if (_graphic->isMousePressed())
                onClick->setClicked(true);
            std::pair<float, float> mousePos = _graphic->getMousePosition();
            if (type->getType() == Type::BUTTONBIND)
                changeText(entity->getID(), getKey(onClick->getAction(), KeyBoard::Unknown), _graphic);
            if (mousePos.first >= rectangle->getX() && mousePos.first <= rectangle->getX() + rectangle->getWidth() &&
                mousePos.second >= rectangle->getY() && mousePos.second <= rectangle->getY() + rectangle->getHeight())
            {
                if (onClick->getClicked() && type->getType() == Type::BUTTON)
                {
                    onClick->setClicked(false);
                    msgToSend.push_back(std::make_pair(onClick->getAction(), entity->getID()));
                }

                if (onClick->getClicked() && type->getType() == Type::BUTTONBIND)
                {
                    KeyBoard key = _graphic->getKeyPressed();
                    if (key != KeyBoard::Unknown)
                    {
                        onClick->setClicked(false);
                        bindTheKey(key, onClick->getAction());
                        changeText(entity->getID(), key, _graphic);
                        changeInput(entities, key, onClick->getAction());
                    }
                }
            }
            if (onClick->getClicked() && type->getType() == Type::BUTTON)
                onClick->setClicked(false);
        }
    }
}

/**
 * @brief Factory function to create a new ButtonSystem.
 *
 * This function creates and returns a new instance of the ButtonSystem class.
 *
 * @param componentManager Reference to the ComponentManager instance.
 * @param entityManager Reference to the EntityManager instance.
 * @param graphic Shared pointer to an IGraphic instance.
 * @param stringCom StringCom instance for string communication.
 *
 * @return Pointer to the newly created ButtonSystem instance.
 */
EXPORT_API ECS_system::ISystem *
createSystem(component::ComponentManager &componentManager,
             entity::EntityManager &entityManager, std::shared_ptr<IGraphic> graphic, std::shared_ptr<IAudio> audio, ECS_system::StringCom stringCom)
{
    return new ECS_system::ButtonSystem(componentManager, entityManager, graphic, audio, stringCom);
}