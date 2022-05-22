// Copyright 2022 Petrova Kseniya <petrovaKI>
#include "Log.hpp"

//логирование - info
void Loger::Write(const std::string_view& message) const {
  *out_ << "[info] " << message << std::endl;
}
//логирование - debug
void Loger::WriteDebug(const std::string_view& message) const {
  if (level_) *out_ << "[debug] " << message << std::endl;
}
//получаем объект
Loger& Loger::GetInstance() {
  static Loger instance;
  return instance;
}
//устанавливаем уровень логирования
void Loger::Setting(bool level) {
  level_ = level;
}
