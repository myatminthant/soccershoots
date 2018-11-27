#ifndef PTPSCORECONTROLLER_H
#define PTPSCORECONTROLLER_H

#include <unordered_map>
#include <string>

class PTPScoreController
{
public:
    class Scores
    {
    public:
        template <typename Type>
        class Score
        {
        public:
            friend class PTPScoreController;

            template <typename Char, typename Traits, typename ScoreType>
            friend std::basic_istream<Char, Traits>& operator>> (std::basic_istream<Char, Traits> &stream, Score<ScoreType> &score);

            template <typename Char, typename Traits, typename ScoreType>
            friend std::basic_ostream<Char, Traits>& operator<< (std::basic_ostream<Char, Traits> &stream, const Score<ScoreType> &score);

            Score(): _current(0), _best(0), _total(0), _snapshot(nullptr) {}
            Score(const Score &other) {
                _current = other.current();
                _best = other.best();
                _total = other.total();

                if (other._snapshot) {
                    _snapshot = new Score<Type>(*other._snapshot);
                }
                else {
                    _snapshot = nullptr;
                }
            }

            ~Score() { delete _snapshot; }

            inline Score& operator= (const Score &other) {
                _current = other.current();
                _best = other.best();
                _total = other.total();

                if (other._snapshot) {
                    if (_snapshot) {
                        *_snapshot = *other._snapshot;
                    }
                    else {
                        _snapshot = new Score<Type>(*other._snapshot);
                    }
                }
                else {
                    delete _snapshot;
                    _snapshot = nullptr;
                }

                return *this;
            }

            inline Score& operator-= (const Score &other) {
                _current -= other.current();

                if (_current < 0) {
                    _current = 0;
                }

                return *this;
            }

            inline Type current() const { return _current; }
            inline Type best() const { return _best; }
            inline Type total() const { return _total; }

            inline void setCurrent(Type value) {
                _current = value;

                if (_current > _total) {
                    _total = _current;
                }

                if (_current > _best) {
                    _best = _current;
                }
            }

            inline void addCurrent(Type value) {
                _current += value;
                _total += value;

                if (_current > _best) {
                    _best = _current;
                }
            }

            inline void decreaseTotal(Type value) {
                _total -= value;

                if (_current > _total) {
                    _current = _total;
                }
            }

            inline void reset(bool full = false) {
                _current = 0;

                if (full) {
                    _total = 0;
                    _best = 0;
                }

                makeSnapshot();
            }

            inline void makeSnapshot() {
                if (!_snapshot) {
                    _snapshot = new Score<Type>();
                }

                _snapshot->_current = _current;
            }

            inline void loadSnapshot() {
                if (_snapshot) {
                    _current = _snapshot->current();
                }
                else {
                    _current = 0;
                }
            }

        private:
            Type _current;
            Type _best;
            Type _total;

            Score<Type> *_snapshot;
        };

        inline Scores& operator-= (const Scores &other) {
            distance -= other.distance;
            points -= other.points;
            coins -= other.coins;

            return *this;
        }

        inline void makeSnapshots() {
            distance.makeSnapshot();
            points.makeSnapshot();
            coins.makeSnapshot();
        }

        inline void loadSnapshots() {
            distance.loadSnapshot();
            points.loadSnapshot();
            coins.loadSnapshot();
        }

        inline void reset(bool full = false) {
            distance.reset(full);
            points.reset(full);
            coins.reset(full);
        }

    public:
        Score<float> distance;
        Score<int> points;
        Score<int> coins;
    };

    static inline Scores& scores(const std::string &name = std::string()) { return _scores[name]; }
    static Scores& currentScreenScores();

    static float currentGlobalDistance();
    static int currentGlobalPoints();
    static int currentGlobalCoins();

    static void resetAll(bool distance, bool points, bool coins, bool full = false);

    static inline void clear() { _scores.clear(); }
    static inline std::size_t count() { return _scores.size(); }

    static std::string toString();
    static void fromString(const std::string &version, const std::string &str, bool reset = true);

private:
    static void fromString(const std::string &str, bool reset = true);
    static void fromString211(const std::string &str, bool reset = true); //Before 2.1.1 (excluding 2.1.0)

private:
    static std::unordered_map<std::string, Scores> _scores;
};

#endif // PTPSCORECONTROLLER_H
