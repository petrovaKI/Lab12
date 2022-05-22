// Copyright 2022 Petrova Kseniya <petrovaKI>
#include "StatSender.hpp"

void Statistic::AsyncSend(const std::vector<Item>& items,
                          std::string_view path) {
  //логирование (info) - записываем путь
  Loger::GetInstance().Write(path);
  //логирование (info) - записываем размер вектора из структур
  Loger::GetInstance().Write("(StatSender) Send stat " +
                             std::to_string(items.size()));

  for (const auto& item : items) {
    //логирование (debug) - записываем id каждого элемента в векторе
    Loger::GetInstance().WriteDebug("send: " + item.id);
    //в файл выводиим все поля каждого элемента вектора
    fstr << item.id << item.name << item.score;
    //синхронизация буфера поткока
    fstr.flush();
  }
}

void Statistic::OnLoaded(const std::vector<Item>& new_items) {
  //логирование (debug)
  Loger::GetInstance().WriteDebug("StatSender::OnDataLoad "
      "(StatSender)");
  //записываем всё в файл вектор
  AsyncSend(new_items, "/items/loaded (StatSender)");
}

void Statistic::Skip(const Item& item) {
  //записываем всё в файл одну структуру
  AsyncSend({item}, "/items/skiped");
}
