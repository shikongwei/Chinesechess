from pygame import mixer
from pygame import time
import sys
mixer.pre_init()
mixer.init(frequency=16000,channels=1,size=-16,buffer=4096)
mixer.music.load('/home/shikw/Design/Develop/Audio/'+str(sys.argv[1])+'.mp3')
mixer.music.play()
while mixer.music.get_busy():
	time.Clock().tick(10)
print 1
def play(musicfile):
	path='/home/shikw/Design/Develop/Audio/'
	musicfile=path+musicfile+'.mp3'
	mixer.music.load(musicfile)
	mixer.music.play()
