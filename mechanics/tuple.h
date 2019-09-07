class Tuple{

  public:
    // Tuple Initializiation 
    float x, y, z, w;
    //Constructor
    Tuple () {};
    Tuple (float i1 = 0, float i2 = 0, float i3 = 0):
      x(i1), y(i2), z(i3) {}

    //Operators
    Tuple operator+(const Tuple& rhs) const;
    Tuple operator-(const Tuple& rhs) const;
    Tuple operator*(float scalar) const;

    //Methods
    float dot(const Tuple& other) const;
    float isPoint() const;
    float isVector() const;

};

//Operators
Tuple Tuple::operator+(const Tuple& rhs) const
{
  return Tuple(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
}

Tuple Tuple::operator-(const Tuple& rhs) const
{
  return Tuple(x - rhs.x, y - rhs.y, z - rhs.z, w + rhs.w);
}

Tuple Tuple::operator*(float scalar) const
{
  return Tuple(scalar * x, scalar * y, scalar * z, scalar * w);
}

Tuple operator*(float scalar, const Tuple vec)
{
  return Tuple(scalar * vec.x, scalar * vec.y, scalar * vec.z, scalar * w);
}

//Methods
float Tuple::dot(const Tuple& other) const
{
  float result = this->x * other.x;
  result += this->y * other.y;
  result += this->z * other.z;
  result += this->w * other.w;
  return result;
}

float Tuple::isPoint() const
{
  return this->w == 1;
}

float Tuple::isVector() const
{
  return this->w == 0;
}


//Generators
float point(const float x, const float y, const float z) const
{
  return Tuple{x, y, z, 1.0}
}

float vector(const float x, const float y, const float z) const
{
  return Tuple{x, y, z, 0.0}
}
