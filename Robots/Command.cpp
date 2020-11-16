#include "Command.h"

MoveCommand::MoveCommand(Mode *mode, Direction dir) {
    this->mode = mode;
    this->dir = dir;
}

void MoveCommand::execute() {
    mode->move(dir);
}

GrabCommand::GrabCommand(Mode *mode) {
    this->mode = mode;
}

void GrabCommand::execute() {
    mode->grab();
}

ScanCommand::ScanCommand(Mode *mode) {
    this->mode = mode;
}

void ScanCommand::execute() {
    mode->scan();
}

SapperCommand::SapperCommand(Mode *mode, bool enable) {
    this->mode = mode;
    this->enable = enable;
}

void SapperCommand::execute() {
    this->mode->toggleSapper(enable);
}

ChangeModeCommand::ChangeModeCommand(Mode **mode, Mode *new_mode) {
    this->mode = mode;
    this->new_mode = new_mode;
}

void ChangeModeCommand::execute() {
    delete *mode;
    *mode = new_mode;
}
