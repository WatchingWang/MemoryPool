template <typename T>
class MemoryPool {
 public:
  explicit MemoryPool(const size_t max_count) {
    max_count_ = max_count;
    head_ = new MemoryNode[max_count];
    auto temp = head_;
    for (size_t i = 1; i < max_count; ++i) {
      temp->next = temp + sizeof(T);
      temp = temp->next;
    }
  }

  template <typename... Args>
  T* GetOne(Args... args) {
    if (cur_use_count_ == max_count_) {
        return nullptr;
    }

    MemoryNode* temp = head_;
    head_ = head_->next;
    ::new (&temp->self) T(std::forward<Args>(args)...);
    --cur_use_count_;
    return &temp->self;
  }

  void RecycleOne(T* ptr) {
    auto temp = reinterpret_cast<MemoryNode*>(ptr);
    temp->next = head_;
    head_ = temp;
    ++cur_use_count_;
  }

 private:
  union MemoryNode {
    MemoryNode* next;
    T self;
  };

  size_t max_count_ = 0;
  size_t cur_use_count_ = 0;
  MemoryNode* head_ = nullptr;
};
