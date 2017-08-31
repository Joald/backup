class SubtitleListenerImpl : public pp::SubtitleListener_Samsung {
 public:
    SubtitleListenerImpl(pp::MediaPlayer_Samsung* player)
      : pp::SubtitleListener_Samsung(player) { }

  explicit SubtitleListenerImpl(
      std::shared_ptr<SubtitleListener> listener)
      : listener_(listener) {
  }

  SubtitleListenerImpl(const SubtitleListenerImpl& other)
      : listener_(other.listener_) {
  }

  SubtitleListenerImpl& operator=(const SubtitleListenerImpl& other) {
    if (this == &other) return *this;

    listener_ = other.listener_;
    return *this;
  }

  virtual ~SubtitleListenerImpl() { }

  void SetListener(SubtitleListener* listener) {
     listener_ =  listener;
  }

  void OnShowSubtitle(PP_TimeDelta duration, const char* text) override {
    if (listener_)
      listener_->OnShowSubtitle(Internal::fromPPTimeDelta(duration), text);
  }

 private:
  SubtitleListener* listener_ = NULL;
};