# Converting Frequency in Mechanical Vibrations to Amplitude Modulation Frequency in Mid-air Ultrasound Vibrations

We propose a perceptual model that translates the frequency spectrum [ $f_{0}^{M}, f_{1}^{M}$ ] in mechanical vibrations into the amplitude modulation (AM) frequency spectrum [ $f_{0}^{U}, f_{1}^{U}$ ] in ultrasound vibrations, aiming to create ultrasound Tactons that can provide a similar perceptual frequency variation of mechanical Tactons.
This model preserves a ratio derived from the change in the frequency spectrum ( $(f_{1}^{M}-f_{0}^{M})/f_{0}^{M}$ ) relative to the JND at the base frequency ( $f_{0}^{M}$ ) in mechanical vibrations, using the following equation as:

$$
f_{0}^{U} = f_{0}^{M}, \quad  f_{1}^{U} = f_{1}^{M} + (f_{1}^{M} - f_{0}^{M}) \times \frac{JND_{0}^{U}}{JND_{0}^{M}}
$$

where $JND_{0}^{U}$ is AM frequency JND at $f_{0}^{U}$ in ultrasound vibrations and $JND_{0}^{M}$ is frequency JND at $f_{0}^{M}$ in mechanical vibrations.

For example, imagine a designer wants to create an ultrasound Tacton that can provide a similar perceptual frequency variation of **Alarm2** [1], a mechanical Tacton that alternates frequencies of 100Hz ( $f_{0}^{M}$ ) and 200Hz ( $f_{1}^{M}$ ).
Based on JNDs of frequency in mechanical and AM frequency in ultrasound vibrations [1, 2], assuming that the AM frequency JND at 100Hz is 73% and the frequency JND at 100Hz is 25% (i.e., $JND_{0}^{U}$ = 73% and $JND_{0}^{M}$ = 25%), the designer could utilize AM frequencies of 100Hz ( $f_{0}^{U}$ ) and 392Hz ( $f_{1}^{U}$ ) instead of 100Hz and 200Hz.
Future studies on translating the frequency of mechanical vibrations to the AM frequency of ultrasound vibrations must validate the perceptual space of ultrasound Tactons derived by this perceptual model and integrate this model with a perceived intensity model.

## Reference
[1] Lim, C., Park, G., & Seifi, H. (2024, May). Designing Distinguishable Mid-Air Ultrasound Tactons with Temporal Parameters. In Proceedings of the 2024 CHI Conference on Human Factors in Computing Systems.

[2] Israr, A., Tan, H. Z., & Reed, C. M. (2006). Frequency and amplitude discrimination along the kinesthetic-cutaneous continuum in the presence of masking stimuli. The Journal of the Acoustical society of America, 120(5), 2789-2800.
