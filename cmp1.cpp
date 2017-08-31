class EventsListenerImpl : public pp::MediaEventsListener_Samsung {
 public:
  EventsListenerImpl(pp::MediaPlayer_Samsung* player)
    : pp::MediaEventsListener_Samsung(player) { }

  explicit EventsListenerImpl(std::shared_ptr<MediaEventsListener> listener)
      : listener_(&(*listener)) {
  }
  explicit EventsListenerImpl(MediaEventsListener* listener)
      : listener_(listener) {
  }

  EventsListenerImpl(const EventsListenerImpl& other)
      : listener_(other.listener_) {
  }

  EventsListenerImpl& operator=(const EventsListenerImpl& other) {
    if (this == &other) return *this;

    listener_ = other.listener_;
    return *this;
  }

  virtual ~EventsListenerImpl() { }

  void SetListener(MediaEventsListener* listener) {
     listener_ =  listener;
  }

  void OnTimeUpdate(PP_TimeTicks time) override {
    if (listener_)
      listener_->OnTimeUpdate(Internal::fromPPTimeTicks(time));
  }

  void OnEnded() override {
    if (listener_)
      listener_->OnEnded();
  }

  void OnError(PP_MediaPlayerError error) override {
    if (listener_)
      listener_->OnError(fromPPMediaPlayerError(error));
  }

 private:
  MediaEventsListener* listener_ = NULL;
};

