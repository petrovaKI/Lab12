// Copyright 2022 Petrova Kseniya <petrovaKI>
#include "Histogram.hpp"
int Histogram::Get_num() const {
  return num;
}
Histogram& Histogram::GetInstance() {
  static Histogram instance;
  return instance;
}
void Histogram::Set_svg(const float& avg_) {
  avg = avg_;
}
void Histogram::PlusNumSkip() {
  ++num;
}
void Histogram::NewLap() {
  num = 0;
}
float Histogram::Get_avg() const {
  return avg;
}
