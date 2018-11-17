#include <iostream>
#include <vector>

typedef unsigned char byte;

struct IInputStream {
  virtual bool Read(byte& value) = 0;
};

struct IOutputStream {
  virtual void Write(byte value) = 0;
};

void Encode(IInputStream& original, IOutputStream& compressed);
void Decode(IInputStream& compressed, IOutputStream& original);

class OutputBitsWriter {
 public:
  explicit OutputBitsWriter(IOutputStream& target_stream);
  ~OutputBitsWriter();
  OutputBitsWriter(const OutputBitsWriter&) = delete;
  OutputBitsWriter(OutputBitsWriter&&) = delete;
  OutputBitsWriter& operator=(const OutputBitsWriter&) = delete;
  OutputBitsWriter& operator=(OutputBitsWriter&&) = delete;

  void WriteBit(bool bit);
  void WriteByte(byte value);

 private:
  IOutputStream& target_stream_;
  byte buffer_;
  int bits_in_buffer_;
};

OutputBitsWriter::OutputBitsWriter(IOutputStream& target_stream)
    : target_stream_(target_stream), buffer_(0), bits_in_buffer_(0) {}

OutputBitsWriter::~OutputBitsWriter() {
  if (bits_in_buffer_ > 0) {
    target_stream_.Write(buffer_);
  }
}

void OutputBitsWriter::WriteBit(bool bit) {
  if (bit) {
    buffer_ |= 1 << bits_in_buffer_;
  }
  ++bits_in_buffer_;
  if (bits_in_buffer_ == 8) {
    target_stream_.Write(buffer_);
    buffer_ = 0;
  }
}

void OutputBitsWriter::WriteByte(byte value) {
  if (bits_in_buffer_ == 0) {
    target_stream_.Write(value);
  } else {
    buffer_ |= value << bits_in_buffer_;
    target_stream_.Write(buffer_);
    buffer_ = value >> (8 - bits_in_buffer_);
  }
}

class SuperOutputStream : public IOutputStream {
 public:
  void Write(byte value) final;
  void Print();

 private:
  std::vector<byte> result;
};

void SuperOutputStream::Write(byte value) {
  result.push_back(value);
}

void SuperOutputStream::Print() {
  for (const byte& value : result) {
    std::cout << static_cast<int>(value) << " ";
  }
}

int main() {
  SuperOutputStream output;
  {
    OutputBitsWriter writer(output);
    writer.WriteByte(100);
    writer.WriteByte(150);
    writer.WriteBit(0);
    writer.WriteBit(1);
    writer.WriteByte(1);
  }
  output.Print();
  return 0;
}