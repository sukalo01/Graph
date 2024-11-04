#include "Node.h"

Node::Node(const std::string& names) :name(names) {}

std::string Node::Node_name()const
{
	return name;
}