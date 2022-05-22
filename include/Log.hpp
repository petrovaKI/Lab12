// Copyright 2022 Petrova Kseniya <petrovaKI>
#ifndef INCLUDE_LOG_HPP_
#define INCLUDE_LOG_HPP_
#include <iostream>
#include <string>
//класс отвечает за логирование
//реализован через синглтон
class Loger {
 public:
  static Loger& GetInstance();

  void Setting(bool level);

  void Write(const std::string_view& message) const;

  void WriteDebug(const std::string_view& message) const;

 private:
  Loger(): level_(false), out_(&std::cout){}

  Loger( const Loger&) = delete;
  Loger& operator=(Loger& ) = delete;

  bool level_ = false;
  mutable std::ostream* out_;
};

struct Item {
  std::string id;
  std::string name;
  float score = 0;
};
#endif  // INCLUDE_LOG_HPP_
