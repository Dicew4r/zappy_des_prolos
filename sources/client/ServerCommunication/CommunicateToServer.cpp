/*
** EPITECH PROJECT, 2018
** server
** File description:
** source
*/

#include <algorithm>
#include <iostream>
#include <fcntl.h>
#include "CommunicateToServer.hpp"

clientSpace::CommunicateToServer::CommunicateToServer(ParseArgs *parse) : _parse(parse)
{
	_client = std::make_unique<Client>();
}

int	clientSpace::CommunicateToServer::connectToServer()
{
	int flag;

	_fd = _client->connectFct(_parse->getIp().c_str(), _parse->getPort());

	if (_fd == 84)
		return 84;
	flag = fcntl(_fd, F_GETFL, 0);
	flag |= O_NONBLOCK;
        fcntl(_fd, F_SETFL, flag);
	if (teamName() == 84)
		return 84;
	look();
	inventory();
	return 0;
}

int	clientSpace::CommunicateToServer::checkNbrPlayer(std::string str)
{
	std::size_t	pos = str.find(" ");

	if (str == "ko")
		return (-1);
	str.erase(str.begin() + pos, str.end());
	if (str == "team" || str == "ko")
		return (-1);
	return std::stoi(str);
}

int	clientSpace::CommunicateToServer::teamName()
{
	std::string	buffer = "";

	_client->send(_fd, "team-name " + _parse->getName());
	while ((buffer = _client->receive(_fd)) == "");
	if (checkNbrPlayer(buffer) < 0)
		return 84;
	while ((buffer = _client->receive(_fd)) == "");
	findMapSize(buffer);
	return (0);
}

void	clientSpace::CommunicateToServer::findMapSize(std::string str)
{
	int	x = 0;
	int	y = 0;
	std::string	temp = str;
	std::size_t	pos1 = str.find(" ");
	std::size_t	pos2;

	temp.erase(temp.begin() + pos1, temp.end());
	x =  std::stoi(temp);
	str = &str[pos1];
	pos2 = str.find(" ");
	str.erase(str.begin() + pos1 + pos2 + 1, str.end());
	y =  std::stoi(str);
	_mapSize = std::make_pair(x, y);
}

bool	clientSpace::CommunicateToServer::forward()
{
	std::string	buffer = "";

	_client->send(_fd, "forward");
	while ((buffer += _client->receive(_fd)) == "");
	return interpretString(buffer);
}

bool	clientSpace::CommunicateToServer::right()
{
	std::string	buffer = "";

	_client->send(_fd, "right");
	while ((buffer += _client->receive(_fd)) == "");
	return interpretString(buffer);
}

bool	clientSpace::CommunicateToServer::left()
{
	std::string	buffer = "";

	_client->send(_fd, "left");
	while ((buffer += _client->receive(_fd)) == "");
	return interpretString(buffer);
}

std::vector<std::vector<clientSpace::tilesType>>	clientSpace::CommunicateToServer::look()
{
	std::string	buffer = "";

	_client->send(_fd, "look");
	while ((buffer += _client->receive(_fd)) == "");
	return {interpretTabLook(buffer)};
}

std::vector<int>	clientSpace::CommunicateToServer::inventory()
{
	std::string	buffer = "";

	_client->send(_fd, "inventory");
	while ((buffer += _client->receive(_fd)) == "");
	return interpretTabInventory(buffer);
}

bool	clientSpace::CommunicateToServer::broadcastText()
{
	std::string	buffer = "";

	_client->send(_fd, "Broadcast text");
	while ((buffer += _client->receive(_fd)) == "");
	return interpretString(buffer);
}

int	clientSpace::CommunicateToServer::connectNbr()
{
	_client->send(_fd, "Connect_nbr");
	_client->receive(_fd);
	return 1;
}

bool	clientSpace::CommunicateToServer::forkCmd()
{
	std::string	buffer = "";

	_client->send(_fd, "Fork");
	while ((buffer += _client->receive(_fd)) == "");
	return interpretString(buffer);
}

bool	clientSpace::CommunicateToServer::eject()
{
	std::string	buffer = "";

	_client->send(_fd, "Eject");
	while ((buffer += _client->receive(_fd)) == "");
	return interpretString(buffer);
}

bool	clientSpace::CommunicateToServer::takeObject()
{
	std::string	buffer = "";

	_client->send(_fd, "Take object");
	while ((buffer += _client->receive(_fd)) == "");
	return interpretString(buffer);
}

bool	clientSpace::CommunicateToServer::setObject()
{
	std::string	buffer = "";

	_client->send(_fd, "Set object");
	while ((buffer += _client->receive(_fd)) == "");
	return interpretString(buffer);
}

bool	clientSpace::CommunicateToServer::incantation()
{
	std::string	buffer = "";

	_client->send(_fd, "Incantation");
	while ((buffer += _client->receive(_fd)) == "");
	return interpretString(buffer);
}

const std::vector<std::string> clientSpace::CommunicateToServer::explode(const std::string& s, const char& c)
{
	std::string buff{""};
	std::vector<std::string> v;
	
	for(auto n:s) {
		if (n != c)
			buff+=n;
		else {
			v.push_back(buff);
			buff = "";
		}
	}
	if (buff != "") {
		v.push_back(buff);
	}
	
	return v;
}

std::vector<clientSpace::tilesType>	clientSpace::CommunicateToServer::convertTab(std::vector<std::string> tab)
{
	std::vector<clientSpace::tilesType>	tilesTab;

	for (auto elem : tab) {
		for (auto tile : _correlationTab) {
			if (elem == tile.first)
				tilesTab.push_back(tile.second);
		}
	}
	return tilesTab;
}

std::vector<int>	clientSpace::CommunicateToServer::interpretTabInventory(std::string tab)
{
	tab.erase(std::remove(tab.begin(), tab.end(), '['), tab.end());
	tab.erase(std::remove(tab.begin(), tab.end(), ']'), tab.end());
	std::vector<std::string>	v{explode(tab, ',')};
	std::vector<int>		intsTab;
	std::size_t	pos;

	for (auto n:v) {
		pos = n.find(" ");
		n.erase(n.begin(), n.begin() + pos + 1);
		intsTab.push_back(std::stoi(n));
	}
	return intsTab;
}

std::vector<std::vector<clientSpace::tilesType>>	clientSpace::CommunicateToServer::interpretTabLook(std::string tab)
{
	tab.erase(std::remove(tab.begin(), tab.end(), '['), tab.end());
	tab.erase(std::remove(tab.begin(), tab.end(), ']'), tab.end());	
	std::vector<std::string>				v{explode(tab, ',')};
	std::vector<std::vector<clientSpace::tilesType>>	tilesTab;

	for (auto n:v) {
		std::vector<std::string>	tilesVec{explode(n, ' ')};
		if (n == "")
			tilesVec = {""};
		tilesTab.push_back(convertTab(tilesVec));
	}
	return tilesTab;
}

bool	clientSpace::CommunicateToServer::interpretString(std::string str)
{
	if (str.find("ok") < str.size())
		return (true);
	else if (str.find("ko") < str.size())
		return (true);
}