// Copyright 2022 Petrova Kseniya <petrovaKI>
#ifndef INCLUDE_HISTOGRAM_HPP
#define INCLUDE_HISTOGRAM_HPP

class Histogram{
 public:
  static Histogram& GetInstance();

  [[nodiscard]] int Get_num() const;

  [[nodiscard]] float Get_avg() const;

  void Set_svg(const float& avg_);

  void PlusNumSkip();

  void NewLap();
 private:
  Histogram() = default;
  Histogram( const Histogram&) = delete;
  Histogram& operator=( Histogram& ) = delete;

  int num = 0;
  float avg = 0;
};

#endif  // INCLUDE_HISTOGRAM_HPP
