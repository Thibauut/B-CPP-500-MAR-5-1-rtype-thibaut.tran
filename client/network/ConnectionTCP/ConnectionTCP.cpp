/*
** EPITECH PROJECT, 2023
** Client
** File description:
** Connexion.cpp
*/

#include "ConnectionTCP.hpp"

ClientConnectionTCP::ClientConnectionTCP(const std::string& userName, const std::string& serverIp, const std::string& serverPort)
    : ip_(serverIp),  port_(serverPort), username_(userName), socket_(ioService)
{
    readyGame_ = false;
    try {
        boost::asio::ip::tcp::resolver resolver(ioService);
        boost::asio::ip::tcp::resolver::query query(serverIp, serverPort);
        boost::asio::ip::tcp::resolver::iterator endpointIterator = resolver.resolve(query);

        boost::asio::connect(socket_, endpointIterator);

    } catch (const std::exception& e) {
        exit(84);
        std::cerr << "Server currently closed, Please restart" << std::endl;
        std::cerr << e.what() << std::endl;
    }
}

bool ClientConnectionTCP::sendMessage(const std::string& msg)
{
    if (!socket_.is_open()) {
        std::cerr << "La connexion au serveur n'est pas établie." << std::endl;
        return false;
    }
    // std::vector<boost::asio::const_buffer> buffers;
    // buffers.push_back(boost::asio::buffer(msg));
    socket_.write_some(boost::asio::buffer(msg));
    return true;
}

void ClientConnectionTCP::handleRead(const boost::system::error_code& error, std::size_t bytes_transferred)
{
    if (!error) {
        const char* dataBegin = boost::asio::buffer_cast<const char*>(buffer_.data());
        const char* dataEnd = dataBegin + bytes_transferred;
        std::string responseData(dataBegin, dataEnd);
        readMessage();
    } else {
        std::cerr << "Erreur lors de la lecture du message : " << error.message() << std::endl;
    }
}

void ClientConnectionTCP::readMessage()
{
    int bytes = socket_.read_some(boost::asio::buffer(buff));
    response_ = std::string(buff.begin(), buff.begin() + bytes - 1);
}

void ClientConnectionTCP::run()
{
    if (!socket_.is_open()) {
        std::cerr << "La connexion au serveur a échoué." << std::endl;
        return;
    }
    std::thread readThread([this]() {
        while (1) {}
    });
    readThread.join();
}

std::string ClientConnectionTCP::extractArguments(const std::string&input, const std::string& keyword) {
    const std::string loginKeyword = keyword;
    size_t loginPos = input.find(loginKeyword);

    if (loginPos != std::string::npos)
        return input.substr(loginPos + loginKeyword.length());
    else
        return "";
}

void ClientConnectionTCP::Login()
{
    setMessage("LOGIN \"" + username_ + "\"\n");
    sendMessage(message_);
    message_ = "";
    readMessage();
    readMessage();
    uuid_ = extractArguments(response_, "LOGIN ");
}

void ClientConnectionTCP::Disconnect()
{
    setMessage("DISCONNECT \"" + uuid_ + "\"\n");
    sendMessage(message_);
    message_ = "";
    readMessage();
    std::string tmp = extractArguments(response_, "DISCONNECT ");
    stop();
}

void ClientConnectionTCP::GetPlayerInfo()
{
    // setMessage("GET_PLAYER_INFO \"" + uuid_ + "\"\n");
    // sendMessage(message_);
    // message_ = "";
    // readMessage();
    // std::string tmp = extractArguments(response_, "GET_PLAYER_INFO ");
    // size_t pos = tmp.find(' ');
    // infoName_ = tmp.substr(0, pos);
    // infoLevel_ = tmp.substr(pos + 1);

    // std::cout << "Name : " << infoName_ << std::endl;
    // std::cout << "Level : " << infoLevel_ << std::endl;
}


std::vector<CLI_PlayerWeapon> ClientConnectionTCP::GetPlayerWeapons()
{
    std::lock_guard<std::mutex> lock(mutexGlobal);
    setMessage("GET_PLAYER_WEAPONS \"" + uuid_ + "\"\n");
    sendMessage(message_);
    message_ = "";
    readMessage();
    std::string tmp = extractArguments(response_, "GET_PLAYER_WEAPONS ");
    std::istringstream iss(tmp);
    std::vector<std::string> results;
    std::string token;
    while (std::getline(iss, token, ' '))
        results.push_back(token);
    // std::cout << tmp << std::endl;
    std::vector <CLI_PlayerWeapon> weapons;
    for (int i = 0 ; i < results.size(); i += 4) {
            CLI_PlayerWeapon weapon = CLI_PlayerWeapon(
                results[i + 1],
                results[i + 3],
                results[i],
                results[i + 2]
            );
        weapons.push_back(weapon);
    }
    return weapons;
}
void ClientConnectionTCP::SetPlayerEquipedWeapon(std::string weapon_uuid)
{
    std::lock_guard<std::mutex> lock(mutexGlobal);
    setMessage("SET_EQUIPED_WEAPON \"" + uuid_ + "\" " + "\"" + weapon_uuid + "\"\n");
    std::cout << message_ << std::endl;
    sendMessage(message_);
    message_ = "";
    readMessage();
    std::string tmp = extractArguments(response_, "SET_EQUIPED_WEAPON ");
    std::cout << tmp << std::endl;
}

void ClientConnectionTCP::OpenCase()
{
    setMessage("OPEN_CASE \"" + uuid_ + "\"\n");
    std::cout << message_ << std::endl;
    sendMessage(message_);
    message_ = "";
    readMessage();
    std::string tmp = extractArguments(response_, "OPEN_CASE ");
    std::cout << tmp << std::endl;
}
void ClientConnectionTCP::GetRoomInfo(std::string roomuuid)
{
    players.clear();
    setMessage("GET_ROOM_INFO \"" + roomuuid + "\"\n");
    sendMessage(message_);
    message_ = "";
    readMessage();
    std::string tmp = extractArguments(response_, "GET_ROOM_INFO ");
    std::string delimiter = "\"";
        size_t start = 0;

    std::istringstream stream(tmp);
    size_t pos = 0;
    while (pos < tmp.size()) {
        size_t nameStart = tmp.find_first_not_of(' ', pos);
        if (nameStart == std::string::npos) break;
        size_t nameEnd = tmp.find('"', nameStart + 1);
        if (nameEnd == std::string::npos) break;
        std::string name = tmp.substr(nameStart + 1, nameEnd - nameStart - 1);
        size_t levelStart = tmp.find_first_not_of(' ', nameEnd + 1);
        if (levelStart == std::string::npos) break;
        size_t levelEnd = tmp.find('"', levelStart + 1);
        if (levelEnd == std::string::npos) break;
        std::string slots = tmp.substr(levelStart + 1, levelEnd - levelStart - 1);

        Player *player = new Player;
        player->name = name;
        player->level = slots;
        players.push_back(player);
        pos = levelEnd + 1;
    }
    players.erase(players.begin());
}

void ClientConnectionTCP::GetRoomList()
{
    rooms.clear();
    setMessage("GET_ROOMS\n");
    sendMessage(message_);
    message_ = "";
    if (shouldStop == false)
        readMessage();
    std::string tmp = extractArguments(response_, "GET_ROOMS ");
    std::istringstream stream(tmp);
    size_t pos = 0;

    std::vector<std::string> values;

    while (pos < tmp.size()) {
        if (tmp[pos] == '"') {
            size_t endQuote = tmp.find('"', pos + 1);
            if (endQuote == std::string::npos) {
                break;
            }
            std::string value = tmp.substr(pos + 1, endQuote - pos - 1);
            values.push_back(value);
            pos = endQuote + 1;
        } else {
            pos++;
        }
    }
    if (!values.empty() && values.size() % 3 == 0) {
        for (size_t i = 0; i < values.size(); i += 3) {
            Room *room = new Room;
            room->name = values[i];
            room->slot = values[i + 1];
            room->uuid = values[i + 2];
            rooms.push_back(room);
        }
    }
    response_ = "";

}

void ClientConnectionTCP::CreateRoom(std::string roomName, std::string roomSize, std::string pathName, int gameType, std::string titleFirst)
{
    setMessage("CREATE_ROOM \"" + uuid_ + "\" \"" + roomSize + "\" \""+ roomName + "\" \"" + std::to_string(gameType) + "\" \"" + pathName + "\" \"" + titleFirst + "\"\n");
    sendMessage(message_);
    message_ = "";
    readMessage();
    infoRoomUuid_ = extractArguments(response_, "CREATE_ROOM ");
}

std::string ClientConnectionTCP::JoinRoom(std::string roomuuid , std::string playeruuid)
{
    setMessage("JOIN_ROOM \"" + playeruuid + "\"" + " \"" + roomuuid + "\"" + "\n");
    sendMessage(message_);
    message_ = "";
    readMessage();
    std::string res = extractArguments(response_, "JOIN_ROOM ");
    std::cout << "RESPONSE ======> " + res << std::endl;
    return res;
}

bool ClientConnectionTCP::Ready(std::string roomuuid, std::string playeruuid, std::string& startId, std::string& portUdp)
{
    shouldStop.store(true, std::memory_order_relaxed);
    readyGame_ = false;
    setMessage("READY \"" + playeruuid + "\"" + " \"" + roomuuid + "\"" + "\n");
    sendMessage(message_);
    message_ = "";
    readMessage();
    setMessage("START \"" + playeruuid + "\"" + " \"" + roomuuid + "\"" + "\n");
    sendMessage(message_);
    readMessage();
    if (response_.find("START") != std::string::npos) {
        std::cout << "RESPONSE ======> " + response_ << std::endl;
        std::string res = extractArguments(response_, "START ");
        std::istringstream iss(res);
        std::string port, id;
        if(iss >> id >> port) {
            startId = id;
            portUdp = port;
        }
        startGame = true;
        return true;
    }
    return false;
}

void ClientConnectionTCP::LeaveRoom(std::string roomuuid)
{
    setMessage("LEAVE_ROOM \"" + uuid_ + "\"" + " \"" + roomuuid + "\"" + "\n");
    sendMessage(message_);
    message_ = "";
    readMessage();
}

void ClientConnectionTCP::DeleteRoom(std::string roomuuid)
{
    setMessage("DELETE_ROOM \"" + uuid_ + "\"" + " \"" + roomuuid + "\"" + "\n");
    sendMessage(message_);
    message_ = "";
    readMessage();
}

void ClientConnectionTCP::setMessage(const std::string& message)
{
    message_ = message;
}

boost::asio::ip::tcp::socket& ClientConnectionTCP::getSocket()
{
    return socket_;
}

boost::asio::io_service& ClientConnectionTCP::getService()
{
    return ioService;
}

bool ClientConnectionTCP::getRunning() {
    return this->running_;
}
