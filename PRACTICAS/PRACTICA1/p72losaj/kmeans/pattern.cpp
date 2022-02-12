#include <cassert>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include "pattern.hpp"

Pattern::Pattern(const size_t dim, const int class_label)
{
    //TODO

    assert(dim>=0);

    v_.resize(dim);

    c_ = class_label;

    if(dim>0) min()==max()==0.0;

}

Pattern::Pattern(const float values[], const size_t dim, const int class_label)
{
    assert(dim>0);
    //TODO

      v_.resize(dim);
      c_ = class_label;
      for(int i=0; i<v_.size(); i++)
      {
        v_[i] = values[i];
      }
}

Pattern::Pattern(const Pattern& other)
{
    //TODO
    v_.resize(other.dim());
    c_ = other.class_label();
    for(int i=0; i<v_.size(); i++)
      {
        v_[i] = other[i];
      }
}

Pattern::~Pattern()
{
    //TODO
    ~v_;
}

size_t Pattern::dim() const
{
    //TODO
    return v_.size();
}

int Pattern::class_label() const
{
    //TODO
    return c_;
}

float Pattern::operator [](const size_t idx) const
{
    assert((0 <= idx) && (idx < dim()));
    //TODO
    return v_[idx];
}

float Pattern::sum() const
{
    //TODO
   float suma = 0.0;
    for(int i=0; i<v_.size(); i++)
    {
        suma = suma + v_[i];
    }

    return suma;
}

float Pattern::max() const
{
    //TODO
    float max = 0.0;
    for(int i=0; i<v_.size(); i++)
    {
      if(max < v_[i]) max = v_[i];
    }

    return max;
}

float Pattern::min() const
{
    //TODO
    float min = 999999;
    for(int i=0; i<v_.size(); i++)
    {
        if(min > v_[i]) min = v_[i];
    }

    return min;
}

void Pattern::set_class_label(const int new_label)
{
    //TODO
    c_ = new_label;
}

void Pattern::set_dim(size_t new_dim)
{
    //TODO
    v_.resize(new_dim);
}

void Pattern::set_value(const size_t i, const float new_v)
{
    assert(0<=i && i<dim());
    //TODO
    v_[i] = new_v;
}

void Pattern::set_values(const float values[])
{
    //TODO



    for(int i=0; i<v_.size(); i++)
    {
        v_[i] = values[i];
    }
}

Pattern& Pattern::operator += (const Pattern& o)
{
    assert(o.dim()==dim());
    //TODO
    Pattern aux(*this);
    aux.v_ += o.v_;
    this->v_ = aux.v_;

    return *this;
}

Pattern& Pattern::operator -= (const Pattern& o)
{
    assert(o.dim()==dim());
    //TODO
    Pattern aux(*this);
    aux.v_ -= o.v_;
    this->v_ = aux.v_;
    return *this;
}

Pattern& Pattern::operator *= (const Pattern& o)
{
    assert(o.dim()==dim());
    //TODO
    Pattern aux(*this);
    aux.v_ *= o.v_;
    this->v_ = aux.v_;
    return *this;
}

Pattern& Pattern::operator *= (const float c)
{
    //TODO
    Pattern aux(*this);
    aux.v_ *= c;
    this->v_ = aux.v_;
    return *this;
}

float
distance(const Pattern& a, const Pattern& b)
{
    //TODO
  
    assert( a.dim() == b.dim() );

    Pattern aux;

    aux = (a-b);

    aux *= aux;

    return sqrt(aux.sum());



}


std::ostream& operator << (std::ostream& output, const Pattern& p)
{
    output << p.class_label();
    for (size_t i=0; i<p.dim(); ++i)
        output << ' ' << p[i];
    output << std::endl;
    return output;
}

std::istream& operator >> (std::istream& input, Pattern& p)
    noexcept(false)
{
   std::string line;
   std::getline(input, line);
   if (input && line.size()>0)
   {
       std::istringstream _input;
       _input.str(line);
       int class_label;
       std::vector<float> values;
       _input >> class_label;
       float v;

       while(_input>>v)
       {
          if (_input)
              values.push_back(v);
       }

       p.set_dim(values.size());

       if (values.size() != p.dim())
           throw std::runtime_error("Wrong input format.");
       else
       {
           p.set_class_label(class_label);
           p.set_values(&values[0]);
       }
   }
   return input;
}


std::istream&
load_dataset(std::istream& input,
             std::vector<Pattern>& dts) noexcept(false)
{
    if (input)
    {
        size_t size;
        size_t dim;
        input >> size >> dim;
        if (!input)
            throw (std::runtime_error("Error: wrong input format."));
        input.ignore(); //Skips newline.
        dts.resize(size, Pattern(dim));
        for (size_t i = 0; i<size; ++i)
        {
            input >> dts[i];
            if (!input)
                throw (std::runtime_error("Error: wrong input format."));
        }
    }
    return input;
}
