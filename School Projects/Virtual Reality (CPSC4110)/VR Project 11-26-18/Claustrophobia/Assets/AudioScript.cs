using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(AudioSource))]
public class AudioScript : MonoBehaviour
{
    public AudioClip intro;
    public AudioClip explanation;
    public AudioClip numbers;
    public AudioSource Source;
    void Start()
    {
        GetComponent<AudioSource>().loop = true;
        StartCoroutine(playEngineSound());
    }

    IEnumerator playEngineSound()
    {
        Source.clip = intro;
        Source.Play();
        yield return new WaitForSeconds(Source.clip.length);
        Source.clip = explanation;
        Source.Play();
        yield return new WaitForSeconds(Source.clip.length);
        Source.clip = numbers;
        Source.Play();

    }
}
