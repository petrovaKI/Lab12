// Copyright 2022 Petrova Kseniya <petrovaKI>
#ifndef INCLUDE_PADECONTAINER_HPP_
#define INCLUDE_PADECONTAINER_HPP_

#include <algorithm>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>

#include "Histogram.hpp"
#include "Log.hpp"
#include "StatSender.hpp"
#include "UsedMemory.hpp"

constexpr size_t kMinLines = 10;

class PageContainer {
 public:
  void RawLoad(std::istream& file);

  [[nodiscard]] const Item& ByIndex(const size_t& i) const;

  [[nodiscard]] const Item& ById(const std::string& id) const;

  [[nodiscard]] size_t GetRawDataSize() const;

  [[nodiscard]] size_t GetDataSize() const;

  void DataLoad(const float& threshold);

  bool IsCorrect(std::string& line);

  void PrintTable() const;

  explicit PageContainer(UsedMemory* memory_counter = new UsedMemory(),
                         Statistic* statistic_sender = new Statistic())
      : memory_counter_(memory_counter), statistic_sender_(statistic_sender){}

  ~PageContainer();

 private:
  UsedMemory* memory_counter_;
  Statistic* statistic_sender_;
  std::vector<Item> data_;
  std::vector<std::string> raw_data_;
};

#endif  // INCLUDE_PADECONTAINER_HPP_
