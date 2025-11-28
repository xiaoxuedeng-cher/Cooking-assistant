import { useState, useEffect, useCallback } from 'react';
import { RecipeStep } from '@/types/recipe';
import { Button } from '@/components/ui/button';
import { Check, ChevronRight, Clock, Pause, Play, Timer as TimerIcon } from 'lucide-react';
import { formatTime } from '@/utils/recipeParser';

interface StepCardProps {
  step: RecipeStep;
  isActive: boolean;
  isCompleted: boolean;
  onComplete: () => void;
  stepNumber: number;
  totalSteps: number;
}

export function StepCard({ 
  step, 
  isActive, 
  isCompleted, 
  onComplete, 
  stepNumber,
  totalSteps 
}: StepCardProps) {
  const [timeLeft, setTimeLeft] = useState(step.duration || 0);
  const [isRunning, setIsRunning] = useState(false);
  const [timerCompleted, setTimerCompleted] = useState(false);
  const [timerStarted, setTimerStarted] = useState(false);

  // Reset timer when step changes
  useEffect(() => {
    if (isActive && step.duration) {
      setTimeLeft(step.duration);
      setIsRunning(false);
      setTimerCompleted(false);
      setTimerStarted(false);
    }
  }, [isActive, step.id, step.duration]);

  const playAlarm = useCallback(() => {
    const audioContext = new (window.AudioContext || (window as any).webkitAudioContext)();
    
    const playBeep = (frequency: number, startTime: number, duration: number) => {
      const oscillator = audioContext.createOscillator();
      const gainNode = audioContext.createGain();
      
      oscillator.connect(gainNode);
      gainNode.connect(audioContext.destination);
      
      oscillator.frequency.value = frequency;
      oscillator.type = 'sine';
      
      gainNode.gain.setValueAtTime(0.3, startTime);
      gainNode.gain.exponentialRampToValueAtTime(0.01, startTime + duration);
      
      oscillator.start(startTime);
      oscillator.stop(startTime + duration);
    };

    const now = audioContext.currentTime;
    playBeep(880, now, 0.2);
    playBeep(880, now + 0.3, 0.2);
    playBeep(1046, now + 0.6, 0.4);
  }, []);

  useEffect(() => {
    let interval: NodeJS.Timeout;

    if (isRunning && timeLeft > 0) {
      interval = setInterval(() => {
        setTimeLeft((prev) => {
          if (prev <= 1) {
            setIsRunning(false);
            setTimerCompleted(true);
            playAlarm();
            return 0;
          }
          return prev - 1;
        });
      }, 1000);
    }

    return () => clearInterval(interval);
  }, [isRunning, timeLeft, playAlarm]);

  const handleMainButtonClick = () => {
    if (!step.duration || timerCompleted) {
      // No timer or timer completed - go to next step
      onComplete();
    } else if (!timerStarted) {
      // Timer not started yet - start it
      setTimerStarted(true);
      setIsRunning(true);
    } else if (isRunning) {
      // Timer running - pause it
      setIsRunning(false);
    } else {
      // Timer paused - resume it
      setIsRunning(true);
    }
  };

  const getButtonContent = () => {
    if (!step.duration || timerCompleted) {
      return (
        <>
          <Check className="w-6 h-6" />
          Done with this step
          <ChevronRight className="w-5 h-5" />
        </>
      );
    }
    
    if (!timerStarted) {
      return (
        <>
          <Play className="w-6 h-6" />
          Start Timer
          <span className="tabular-nums font-bold">{formatTime(step.duration)}</span>
        </>
      );
    }
    
    if (isRunning) {
      return (
        <>
          <Pause className="w-6 h-6" />
          <span className="tabular-nums font-bold text-xl">{formatTime(timeLeft)}</span>
          <span className="text-sm opacity-80">Tap to pause</span>
        </>
      );
    }
    
    return (
      <>
        <Play className="w-6 h-6" />
        <span className="tabular-nums font-bold text-xl">{formatTime(timeLeft)}</span>
        <span className="text-sm opacity-80">Tap to resume</span>
      </>
    );
  };

  const progress = step.duration ? ((step.duration - timeLeft) / step.duration) * 100 : 0;

  if (!isActive && !isCompleted) {
    // Upcoming step - compact view
    return (
      <div className="opacity-50 p-4 rounded-xl bg-card/50 border border-border/30">
        <div className="flex items-center gap-3">
          <div className="w-8 h-8 rounded-full bg-muted flex items-center justify-center text-sm font-semibold text-muted-foreground">
            {stepNumber}
          </div>
          <p className="text-muted-foreground line-clamp-1">{step.instruction}</p>
          {step.duration && (
            <div className="ml-auto flex items-center gap-1 text-sm text-muted-foreground">
              <Clock className="w-4 h-4" />
              {formatTime(step.duration)}
            </div>
          )}
        </div>
      </div>
    );
  }

  if (isCompleted) {
    // Completed step
    return (
      <div className="p-4 rounded-xl bg-cooking-success/10 border border-cooking-success/30">
        <div className="flex items-center gap-3">
          <div className="w-8 h-8 rounded-full bg-cooking-success flex items-center justify-center">
            <Check className="w-5 h-5 text-primary-foreground" />
          </div>
          <p className="text-foreground/70 line-through">{step.instruction}</p>
        </div>
      </div>
    );
  }

  // Active step - full view
  return (
    <div className="gradient-card rounded-2xl shadow-elevated p-6 md:p-8 border-2 border-primary/30 animate-scale-in">
      <div className="flex items-center gap-3 mb-4">
        <div className="w-10 h-10 rounded-full gradient-warm flex items-center justify-center text-lg font-bold text-primary-foreground">
          {stepNumber}
        </div>
        <div>
          <p className="text-sm font-medium text-muted-foreground">
            Step {stepNumber} of {totalSteps}
          </p>
          <div className="flex gap-1 mt-1">
            {Array.from({ length: totalSteps }).map((_, i) => (
              <div 
                key={i}
                className={`h-1.5 rounded-full transition-all ${
                  i < stepNumber 
                    ? 'w-4 bg-primary' 
                    : i === stepNumber - 1 
                      ? 'w-6 bg-primary' 
                      : 'w-2 bg-muted'
                }`}
              />
            ))}
          </div>
        </div>
      </div>

      <p className="text-xl md:text-2xl font-medium text-foreground leading-relaxed mb-6">
        {step.instruction}
      </p>

      {/* Timer progress indicator */}
      {step.duration && timerStarted && !timerCompleted && (
        <div className="mb-4 rounded-xl p-4 transition-all duration-300 bg-primary/10 border border-primary/30">
          <div className="flex items-center gap-3 mb-2">
            <TimerIcon className="w-5 h-5 text-primary" />
            <span className="text-sm font-medium text-muted-foreground">
              {isRunning ? 'Timer running' : 'Timer paused'}
            </span>
          </div>
          <div className="h-2 bg-muted/50 rounded-full overflow-hidden">
            <div 
              className="h-full transition-all duration-1000 bg-primary"
              style={{ width: `${progress}%` }}
            />
          </div>
        </div>
      )}

      {/* Timer completed indicator */}
      {step.duration && timerCompleted && (
        <div className="mb-4 rounded-xl p-4 bg-cooking-success/20 border border-cooking-success">
          <div className="flex items-center gap-3">
            <Check className="w-5 h-5 text-cooking-success" />
            <span className="text-sm font-medium text-cooking-success">Timer complete!</span>
          </div>
        </div>
      )}

      <Button
        variant={timerCompleted || !step.duration ? "cooking" : !timerStarted ? "cooking" : isRunning ? "default" : "outline"}
        size="xl"
        className={`w-full ${
          step.duration && timerStarted && !timerCompleted 
            ? isRunning 
              ? 'bg-primary hover:bg-primary/90'
              : 'border-2 border-primary text-primary hover:bg-primary/10'
            : ''
        }`}
        onClick={handleMainButtonClick}
      >
        {getButtonContent()}
      </Button>
    </div>
  );
}
