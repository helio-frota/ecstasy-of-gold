# ecstasy-of-gold

A C version of [a game I made years ago](https://github.com/helio-frota/g-o-l-d).


The game idea was inspired by a scene from the movie "The Good The Bad The Ugly": 

(The scene: https://www.youtube.com/watch?v=_ZHEu7HusG4)


### Development

> The development environment is based on fedora 29. 

Install the required dependencies:

```console
sudo dnf install allegro5
sudo dnf install allegro5-devel
sudo dnf install allegro5-addon-dialog-devel
sudo dnf install allegro5-addon-audio-devel
sudo dnf install allegro5-addon-image-devel
sudo dnf install allegro5-addon-acodec-devel
sudo dnf install allegro5-addon-ttf-devel
```

#### Build

```console
./build.sh
```

### How to play

Use the vim keys (H, J, K, L) to move and get the maximum amount of gold before the time runs out.

![Alt status](https://raw.githubusercontent.com/helio-frota/ecstasy-of-gold/master/currentstatus.png)
