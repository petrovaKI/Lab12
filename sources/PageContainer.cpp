// Copyright 2022 Petrova Kseniya <petrovaKI>
#include "PageContainer.hpp"
//возвращает одну позицию вектора
const Item& PageContainer::ByIndex(const size_t& i) const {
  return data_[i];
}

const Item& PageContainer::ById(const std::string& id) const {
  //проходит по вектору и ищет заданный id
  auto it = std::find_if(std::begin(data_),
                         std::end(data_),
                         [&id](const auto& i)
                         { return id == i.id; });
  return *it;
}
//функция для вывода в main
void PageContainer::PrintTable() const {
  std::cout << "| id\t |\t\tname\t\t|\tscore\t\t|\n";
  std::string separator = "+________________________________"
      "_______________________________+\n";
  std::cout << separator;
  for (size_t i = 0; i < data_.size(); ++i) {
    const auto& item = ByIndex(i);
    std::cout << "|   " << item.id << "\t |\t\t" <<
        item.name << "\t\t|\t" << item.score << "\t\t|" << std::endl;
    const auto& item2 = ById(std::to_string(i));
    std::cout << "|   " << item2.id << "\t |\t\t" <<
        item2.name << "\t\t|\t" << item2.score << "\t\t|" << std::endl;
    std::cout << separator;
  }
}
//построчное считывание из файла
void PageContainer::RawLoad(std::istream& file) {
  std::vector<std::string> raw_data;

  if (!file) throw std::runtime_error("file don`t open");

  if (file.peek() == EOF)  throw std::runtime_error("file is empty");

  Loger::GetInstance().WriteDebug("file open");
  //считываем строки из файла и записываем их в вектор raw_data
  while (!file.eof()) {
    std::string line;
    std::getline(file, line, '\n');
    if (IsCorrect(line)) raw_data.push_back(std::move(line));
  }
  //проверям записано ли минимально-необхожимое количество строк
  if (raw_data.size() < kMinLines) {
    throw std::runtime_error("too small input stream");
  }

  memory_counter_->OnRawDataLoad(raw_data_, raw_data);
  //обновляем использованную память
  raw_data_ = std::move(raw_data);
}
//Ссчитывает нные из строкового поткоа
void PageContainer::DataLoad(const float& threshold) {
  //num = 0
  Histogram::GetInstance().NewLap();
  std::vector<Item> data;
  std::set<std::string> ids;
  float sum = 0;
  size_t counter = 0;
  for (const auto& line : raw_data_) {
    std::stringstream stream(line);

    Item item;
    //считываем все поля
    stream >> item.id >> item.name >> item.score;

    if (auto&& [_, inserted] =
            ids.insert(item.id); !inserted) {
      throw std::runtime_error("already seen");
    }

    if (item.score > threshold) {
      data.push_back(std::move(item));
      sum += item.score;
      ++counter;
    } else {
      statistic_sender_->Skip(item);
      //++num
      Histogram::GetInstance().PlusNumSkip();
    }
  }
  Histogram::GetInstance().Set_svg(sum/counter);
  if (data.size() < kMinLines) {
    throw std::runtime_error("correct items less then const");
  }

  memory_counter_->OnDataLoad(data_, data);
  statistic_sender_->OnLoaded(data);
  data_ = std::move(data);
}

bool PageContainer::IsCorrect(std::string& line) {
  size_t counter = 0;
  bool status = true;
  for (auto& ch : line){
    if (ch == ' ') {
      ++counter;
    } else if (counter == 0) {
      status = (ch >= '0' && ch <= '9') && status;
    } else if (counter == 1) {
      status = ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) && status;
    } else if (counter == 2) {
      status = (ch >= '0' && ch <= '9') && status;
    }
  }
  status = status && (counter == 2);
  return status;
}

size_t PageContainer::GetRawDataSize() const { return raw_data_.size(); }
//возвращает размер массива структур
size_t PageContainer::GetDataSize() const { return data_.size(); }
PageContainer::~PageContainer() {
  delete memory_counter_;
  delete statistic_sender_;
}
