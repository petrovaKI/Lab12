// Copyright 2022 Petrova Kseniya <petrovaKI>
#include "UsedMemory.hpp"

//получение использованной памяти для структур
void UsedMemory::OnDataLoad(const std::vector<Item>& old_items,
                            const std::vector<Item>& new_items) {
  //логирование (debug)
  Loger::GetInstance().WriteDebug("UsedMemory::OnDataLoad");
  for (const auto& item : new_items) {
    used_ += item.id.capacity();
    used_ += item.name.capacity();
    used_ += sizeof(item.score);
  }

  for (const auto& item : old_items) {
    used_ -= item.id.capacity();
    used_ -= item.name.capacity();
    used_ -= sizeof(item.score);
  }
  //логирование (info) - записываем память, использованную
  // под все поля структур в векторе
  Loger::GetInstance().Write("UsedMemory::OnDataLoad: new size = " +
                             std::to_string(used_));
}
//получение использованной памяти для строк
void UsedMemory::OnRawDataLoad(const std::vector<std::string>& old_items,
                               const std::vector<std::string>& new_items) {
  //логирование (debug)
  Loger::GetInstance().WriteDebug("UsedMemory::OnRawDataLoads");
  for (const auto& item : new_items) {
    used_ += item.capacity();
  }
  for (const auto& item : old_items) {
    used_ -= item.capacity();
  }
  //логирование (info) - записываем память, использованную
  // под все элементы в векторе
  Loger::GetInstance().Write("UsedMemory::OnDataLoad: new size = " +
                             std::to_string(used_));
}

size_t UsedMemory::Used() const {
  return used_;
}
