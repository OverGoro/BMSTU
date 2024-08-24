#include "BaseCarcasModelBuilder.h"

BaseCarcasModelBuilder::BaseCarcasModelBuilder(std::shared_ptr<FileCarcassModelReader> &reader)
    : _reader(reader) {}
